#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dctquant.h"
#include "bitmap.h"

// Perform zig-zag decoding.
static void un_zig_zag(const int8_t* input_block, int8_t* output_block)
{
	// TODO
}


// Multiply with the components of the quantization matrix.
static void dequantize(const int8_t* input_block, const uint32_t* quant_matrix, float* output_block)
{
	// TODO
}

// Perform the IDCT on the given block of input data.
static void perform_inverse_dct(const float* input_block, float* output_block)
{
	// TODO
}

// Copy the block at (`index_x`, `index_y`) from `block` into the given pixel buffer.
// The dimensions of the image (in blocks) is given by `blocks_x` * `blocks_y`.
static void write_block(bitmap_pixel_rgb_t* pixels, uint32_t index_x, uint32_t index_y, uint32_t blocks_x, uint32_t blocks_y, const float* block)
{
	uint32_t bytes_per_row = blocks_x * 8;
	uint32_t base_offset = index_y * 8 * bytes_per_row;
	uint32_t col_offset = index_x * 8;

	for (uint32_t curr_y = 0; curr_y < 8; curr_y++)
	{
		uint32_t rowOffset = curr_y * bytes_per_row;

		for (uint32_t curr_x = 0; curr_x < 8; curr_x++)
		{
			uint32_t offset = base_offset + rowOffset + col_offset + curr_x;

			float component = roundf(block[(8 * curr_y) + curr_x]) + 128;
			bitmap_component_t clamped_component = (bitmap_component_t)MAX(0, MIN(component, 255));

			pixels[offset].r = clamped_component;
			pixels[offset].g = clamped_component;
			pixels[offset].b = clamped_component;
		}
	}
}

int decompress(const char* file_path, const uint32_t* quant_matrix, const char* output_path)
{
	// TODO
	return -1;
}
