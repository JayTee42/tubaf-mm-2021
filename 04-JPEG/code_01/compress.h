#ifndef COMPRESS_H
#define COMPRESS_H

// Compress the given bitmap file.
int compress(const char* file_path, const uint32_t* quant_matrix, const char* grayscale_path, const char* output_path);

#endif
