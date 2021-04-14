#include <assert.h>
#include <stdlib.h>

#include "bitmap.h"

static void apply_quant_err_comp(bitmap_component_t* c, int qe, int fac)
{
	int new_c = *c + ((qe * fac) / 16);
	*c = (new_c < 0) ? 0 : (new_c > 255) ? 255 : new_c;
}

static void apply_quant_err(bitmap_pixel_rgb_t* pixels, int width, int height, int x, int y, const int* qe, int fac)
{
	if ((x >= 0) && (x < width) && (y < height))
	{
		bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];

		apply_quant_err_comp(&pix->r, qe[0], fac);
		apply_quant_err_comp(&pix->g, qe[1], fac);
		apply_quant_err_comp(&pix->b, qe[2], fac);
	}
}

static void floyd_steinberg(bitmap_pixel_rgb_t* pixels, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// Get a pointer to the pixel and calculate the black / white value.
			bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];
			bitmap_component_t gs = ((30 * pix->r) + (59 * pix->g) + (11 * pix->b)) / 100;
			bitmap_component_t bw = (gs > 160) * 255;

			// Remember the quantization error in all components before assigning the black / white value.
			int qe[] = { pix->r - bw, pix->g - bw, pix->b - bw };
			pix->r = pix->g = pix->b = bw;

			// Distribute the error onto the neighbours.
			apply_quant_err(pixels, width, height, x + 1, y, qe, 7);
			apply_quant_err(pixels, width, height, x - 1, y + 1, qe, 3);
			apply_quant_err(pixels, width, height, x, y + 1, qe, 5);
			apply_quant_err(pixels, width, height, x + 1, y + 1, qe, 1);
		}
	}
}

int main(void)
{
	// Read the bitmap pixels.
	bitmap_error_t error;
	int width, height;
	bitmap_pixel_rgb_t* pixels;

	error = bitmapReadPixels(
		"sails.bmp",
		(bitmap_pixel_t**)&pixels,
		&width,
		&height,
		BITMAP_COLOR_SPACE_RGB
	);

	assert(error == BITMAP_ERROR_SUCCESS);

	// Manipulate the pixels.
	floyd_steinberg(pixels, width, height);

	// Write the pixels back.
	bitmap_parameters_t params =
	{
		.bottomUp = BITMAP_BOOL_TRUE,
		.widthPx = width,
		.heightPx = height,
		.colorDepth = BITMAP_COLOR_DEPTH_24,
		.compression = BITMAP_COMPRESSION_NONE,
		.dibHeaderFormat = BITMAP_DIB_HEADER_INFO,
		.colorSpace = BITMAP_COLOR_SPACE_RGB
	};

	error = bitmapWritePixels(
		"sails_dither.bmp",
		BITMAP_BOOL_TRUE,
		&params,
		(bitmap_pixel_t*)pixels
	);

	assert(error == BITMAP_ERROR_SUCCESS);

	// Free the memory that has been allocated by the bitmap library.
	free(pixels);

	return 0;
}
