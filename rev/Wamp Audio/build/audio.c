#include "tinywav.h"

#define NUM_CHANNELS 2
#define SAMPLE_RATE 48000
#define BLOCK_SIZE 480

int main() {


    TinyWav tw;
    tinywav_open_write(&tw,
                       NUM_CHANNELS,
                       SAMPLE_RATE,
                       TW_FLOAT32, // the output samples will be 32-bit floats. TW_INT16 is also supported
                       TW_INLINE,  // the samples to be written will be assumed to be inlined in a single buffer.
// Other options include TW_INTERLEAVED and TW_SPLIT
                       "path/to/output.wav" // the output path
    );

    for (int i = 0; i < 100; i++) {
// NOTE: samples are always expected in float32 format,
// regardless of file sample format

        float samples[BLOCK_SIZE * NUM_CHANNELS];
        tinywav_write_f(&tw, samples, BLOCK_SIZE);


    }

    tinywav_close_write(&tw);

}