#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dctquant.h"
#include "bitmap.h"

// Output path can be NULL to suppress the dumping of the grayscale bitmap.
static bitmap_pixel_hsv_t* create_grayscale_bitmap(const char* input_path, const char* output_path, uint32_t* blocks_x, uint32_t* blocks_y)
{
	// TODO
	return NULL;
}

// Copy the block at (`index_x`, `index_y`) from the given pixel buffer into `block`.
// The dimensions of the image (in blocks) is given by `blocks_x` * `blocks_y`.
static void read_block(const bitmap_pixel_hsv_t* pixels, uint32_t index_x, uint32_t index_y, uint32_t blocks_x, uint32_t blocks_y, float* block)
{
	uint32_t bytes_per_row = blocks_x * 8;
	uint32_t base_offset = index_y * 8 * bytes_per_row;
	uint32_t col_offset = index_x * 8;

	for (uint32_t curr_y = 0; curr_y < 8; curr_y++)
	{
		uint32_t row_offset = curr_y * bytes_per_row;

		for (uint32_t curr_x = 0; curr_x < 8; curr_x++)
		{
			block[(8 * curr_y) + curr_x] = pixels[base_offset + row_offset + col_offset + curr_x].v - 128.0f;
		}
	}
}

// Perform the DCT on the given block of input data.
static void perform_dct(const float* input_block, float* output_block)
{
	// TODO
}

// Divide by the components of the quantization matrix and round.
static void quantize(float* input_block, const uint32_t* quant_matrix, int8_t* output_block)
{
	// TODO
}

// Perform zig-zag encoding.
static void zig_zag(int8_t* input_block, int8_t* output_block)
{
	// TODO
}

int compress(const char* file_path, const uint32_t* quant_matrix, const char* grayscale_path, const char* outputPath)
{
	// TODO
	return -1;
}
