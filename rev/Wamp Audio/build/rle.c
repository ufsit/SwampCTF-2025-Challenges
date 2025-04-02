#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Struct to hold encoded data
typedef struct {
    uint8_t* data;   // Encoded data
    size_t length;   // Length of encoded data
} RLEData;

// Function to perform Run-Length Encoding on uint8_t array
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

// Function to perform Run-Length Decoding on uint8_t array
uint8_t* rle_decode_uint8(const uint8_t* input, size_t input_length, size_t* output_length) {
    if (input == NULL || input_length == 0 || input_length % 2 != 0) {
        if (output_length) *output_length = 0;
        return NULL;
    }

    // Calculate total decoded length
    size_t total_decoded_length = 0;
    for (size_t i = 0; i < input_length; i += 2) {
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

// Example usage and testing
int main() {
    // Test data
    uint8_t original[] = {1, 1, 1, 2, 2, 3, 3, 3, 3};
    size_t original_length = sizeof(original) / sizeof(original[0]);

    // Encode
    RLEData encoded = rle_encode_uint8(original, original_length);

    printf("Original: ");
    for (size_t i = 0; i < original_length; i++) {
        printf("%u ", original[i]);
    }
    printf("\n");

    printf("Encoded (count, value pairs): ");
    for (size_t i = 0; i < encoded.length; i += 2) {
        printf("(%u, %u) ", encoded.data[i], encoded.data[i+1]);
    }
    printf("\n");

    // Decode
    size_t decoded_length;
    uint8_t* decoded = rle_decode_uint8(encoded.data, encoded.length, &decoded_length);

    printf("Decoded:  ");
    for (size_t i = 0; i < decoded_length; i++) {
        printf("%u ", decoded[i]);
    }
    printf("\n");

    // Verify
    int verify = (original_length == decoded_length);
    for (size_t i = 0; verify && i < original_length; i++) {
        if (original[i] != decoded[i]) {
            verify = 0;
            break;
        }
    }
    printf("%s\n", verify ? "Encoding and decoding successful!" : "Encoding/decoding failed.");

    // Free dynamically allocated memory
    free(encoded.data);
    free(decoded);

    return 0;
}