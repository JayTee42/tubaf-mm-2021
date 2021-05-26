#ifndef DECOMPRESS_H
#define DECOMPRESS_H

// Decompress the given .dct file.
// A (potentially lossy) grayscale bitmap will be written.
int decompress(const char* file_path, const uint32_t* quant_matrix, const char* output_path);

#endif
