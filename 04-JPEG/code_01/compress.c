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
	// Read the input bitmap:
	bitmap_pixel_hsv_t* pixels;
	uint32_t width_px, height_px;

	bitmap_error_t error = bitmapReadPixels(input_path, (bitmap_pixel_t**)&pixels, &width_px, &height_px, BITMAP_COLOR_SPACE_HSV);

	if (error != BITMAP_ERROR_SUCCESS)
	{
		printf("Failed to read bitmap, does it exist?\n");
		return NULL;
	}

	// Make sure the bitmap has a multiple of 8 pixels in both dimensions:
	if ((width_px % 8) || (height_px % 8))
	{
		printf("Width and height must be a multiple of 8 pixels.\n");
		free(pixels);

		return NULL;
	}

	// Assign the block size:
	*blocks_x = width_px / 8;
	*blocks_y = height_px / 8;

	// Dump the bitmap if requested:
	if (output_path)
	{
		// Convert to grayscale:
		for (uint32_t i = 0; i < (width_px * height_px); i++)
		{
			pixels[i].s = 0;
		}

		bitmap_parameters_t params =
		{
			.bottomUp = BITMAP_BOOL_TRUE,
			.widthPx = width_px,
			.heightPx = height_px,
			.colorDepth = BITMAP_COLOR_DEPTH_24,
			.compression = BITMAP_COMPRESSION_NONE,
			.dibHeaderFormat = BITMAP_DIB_HEADER_INFO,
			.colorSpace = BITMAP_COLOR_SPACE_HSV,
		};

		error = bitmapWritePixels(output_path, BITMAP_BOOL_TRUE, &params, (bitmap_pixel_t*)pixels);

		if (error != BITMAP_ERROR_SUCCESS)
		{
			printf("Failed to write grayscale bitmap.\n");
			free(pixels);

			return NULL;
		}
	}

	return pixels;
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

static float dct_sum(const float* input_block, uint8_t p, uint8_t q)
{
	float sum = 0;

	for (uint8_t m = 0; m < 8; m++)
	{
		for (uint8_t n = 0; n < 8; n++)
		{
			sum += input_block[(8 * m) + n] * cosf((M_PI * (m + 0.5f) * p) / 8.0f) * cosf((M_PI * (n + 0.5f) * q) / 8.0f);
		}
	}

	return sum;
}

// Perform the DCT on the given block of input data.
static void perform_dct(const float* input_block, float* output_block)
{
	for (uint8_t p = 0; p < 8; p++)
	{
		for (uint8_t q = 0; q < 8; q++)
		{
			output_block[(8 * p) + q] = alpha(p) * alpha(q) * dct_sum(input_block, p, q);
		}
	}
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

int compress(const char* file_path, const uint32_t* quant_matrix, const char* grayscale_path, const char* output_path)
{
	// Load the bitmap in grayscale:
	uint32_t blocks_x, blocks_y;
	bitmap_pixel_hsv_t* pixels = create_grayscale_bitmap(file_path, grayscale_path, &blocks_x, &blocks_y);

	if (!pixels)
	{
		return -1;
	}

	// Open the output file (.dct):
	FILE* file = fopen(output_path, "wb");

	if (!file)
	{
		printf("Failed to create output file.\n");
		free(pixels);

		return -1;
	}

	// Write the number of blocks at the start:
	// FIXME: Respect endianness!
	if (fwrite(&blocks_x, sizeof(blocks_x), 1, file) != 1)
	{
		printf("Failed to write the number of blocks in x direction.\n");

		free(pixels);
		fclose(file);

		return -1;
	}

	if (fwrite(&blocks_y, sizeof(blocks_y), 1, file) != 1)
	{
		printf("Failed to write the number of blocks in y direction.\n");

		free(pixels);
		fclose(file);

		return -1;
	}

	// Walk all the blocks:
	for (uint32_t index_y = 0; index_y < blocks_y; index_y++)
	{
		for (uint32_t index_x = 0; index_x < blocks_x; index_x++)
		{
			float input_block[64];
			float dct_block[64];

			// Read the next block:
			read_block(pixels, index_x, index_y, blocks_x, blocks_y, input_block);

			// Execute the actual DCT:
			perform_dct(input_block, dct_block);

			// DEBUG: Print first block!
			if (index_x == 0 && index_y == 0)
			{
				for (size_t i = 0; i < 64; i++)
				{
					printf("%f, ", dct_block[i]);

					if (i % 8 == 7)
					{
						printf("\n");
					}
				}
			}

			// TODO ...
		}
	}

	// TODO

	// Free the pixels:
	free(pixels);

	// Close the output file:
	fclose(file);

	return 0;
}
