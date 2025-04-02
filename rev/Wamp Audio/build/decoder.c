#include "tinywav.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_CHANNELS 1
#define SAMPLE_RATE 44100
#define BLOCK_SIZE 1000

typedef struct {
    uint8_t* data;   // Encoded data
    size_t length;   // Length of encoded data
} RLEData;

RLEData rle_encode_uint8(const uint8_t* input, size_t input_length) {
    RLEData result = {NULL, 0};

    if (input == NULL || input_length == 0) {
        return result;
    }

    // Worst case: no runs, so we need 2x space (count + value for each element)
    result.data = malloc(2 * input_length * sizeof(uint8_t));
    if (result.data == NULL) {
        return result;
    }

    size_t write_index = 0;
    uint8_t current = input[0];
    uint8_t count = 1;

    for (size_t i = 1; i < input_length; i++) {
        if (input[i] == current && count < 255) {
            // Continue current run
            count++;
        } else {
            // Write current run
            result.data[write_index++] = count;
            result.data[write_index++] = current;

            // Reset for new value
            current = input[i];
            count = 1;
        }
    }

    // Write the last run
    result.data[write_index++] = count;
    result.data[write_index++] = current;

    result.length = write_index;
    return result;
}

uint8_t* rle_decode_uint8(const uint8_t* input, size_t input_length, size_t* output_length) {
    if (input == NULL || input_length == 0 || input_length % 2 != 0) {
        if (output_length) *output_length = 0;
        return NULL;
    }

    // Calculate total decoded length
    size_t total_decoded_length = 0;
    for (size_t i = 0; i < input_length; i += 2) {
        //while(input[i] == 0)
         //   i++;
        total_decoded_length += input[i];
    }

    // Allocate decoded array
    uint8_t* decoded = malloc(total_decoded_length * sizeof(uint8_t));
    if (decoded == NULL) {
        if (output_length) *output_length = 0;
        return NULL;
    }

    size_t write_index = 0;
    for (size_t i = 0; i < input_length; i += 2) {
        uint8_t count = input[i];
        uint8_t value = input[i + 1];

        // Repeat the value 'count' times
        for (uint8_t j = 0; j < count; j++) {
            decoded[write_index++] = value;
        }
    }

    if (output_length) *output_length = total_decoded_length;
    return decoded;
}

int main(int argc, char** argv) {

    if(argc == 1){
        puts("Wamp Audio Format"
             "<binary> input.wav output.wamp");
        return 1;
    }

    TinyWav tw_write;
    int errcode = tinywav_open_write(&tw_write,
                                     NUM_CHANNELS,
                                     SAMPLE_RATE,
                                     TW_FLOAT32, // the output samples will be 32-bit floats. TW_INT16 is also supported
                                     TW_INLINE,  // the samples to be written will be assumed to be inlined in a single buffer.
// Other options include TW_INTERLEAVED and TW_SPLIT
                                     argv[2] // the output path
    );
    printf("error code %d\n", errcode);

    TinyWav tw;
    errcode = tinywav_open_read(&tw,
                                argv[1],
                                TW_SPLIT // the samples will be delivered by the read function in split format
    );

    printf("error code %d\n", errcode);

    int blocks = 0;

    for (int i = 0; i < tw.numFramesInHeader / BLOCK_SIZE; i++) {
        printf("blks %d\n", blocks);
        blocks++;
// samples are always provided in float32 format,
// regardless of file sample format
        float samples[NUM_CHANNELS * BLOCK_SIZE * 2];

// Split buffer requires pointers to channel buffers
        float *samplePtrs[NUM_CHANNELS];
        for (int j = 0; j < NUM_CHANNELS; ++j) {
            samplePtrs[j] = samples + j * BLOCK_SIZE;
        }

        tinywav_read_f(&tw, samplePtrs, BLOCK_SIZE * 2);

        //RLEData wam = rle_encode_uint8((uint8_t*)samples, NUM_CHANNELS * BLOCK_SIZE * sizeof(float));
        ssize_t out_len;
        uint8_t *data = rle_decode_uint8((uint8_t*)samples, NUM_CHANNELS * BLOCK_SIZE * sizeof(float) * 2, &out_len);

        //printf("RLE size %d\n", wam.length);

        tinywav_write_f(&tw_write, data, BLOCK_SIZE);

        free(data);

        for (int i = 0; i < 100; i++) {
            //printf("%f\n", samplePtrs[0][i]);
        }
    }

    tinywav_close_read(&tw);
    tinywav_close_write(&tw_write);

}