#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "bitmap.h"

// Comment this line out to disable Floyd-Steinberg dithering.
#define DITHER

// The palette colors to select from
bitmap_pixel_rgb_t PAL[] =
{
	{ .r = 0x00, .g = 0x00, .b = 0x00 }, // Black
	{ .r = 0xFF, .g = 0x00, .b = 0x00 }, // Red
	{ .r = 0x00, .g = 0xFF, .b = 0x00 }, // Green
	{ .r = 0x00, .g = 0x00, .b = 0xFF }, // Blue
	{ .r = 0xFF, .g = 0xFF, .b = 0x00 }, // Yellow
	{ .r = 0xFF, .g = 0x00, .b = 0xFF }, // Pink
	{ .r = 0x00, .g = 0xFF, .b = 0xFF }, // Cyan
	{ .r = 0xFF, .g = 0xFF, .b = 0xFF }  // White
};

// Select the color from the palette that exhibits the minimum Euclidean distance to the given pixel.
static bitmap_pixel_rgb_t select_from_pal(bitmap_pixel_rgb_t pix)
{
	int dist = INT_MAX;
	bitmap_pixel_rgb_t pal;

	for (int i = 0; i < (sizeof(PAL) / sizeof(*PAL)); i++)
	{
		bitmap_pixel_rgb_t new_pal = PAL[i];

		int dr = new_pal.r - pix.r, dg = new_pal.g - pix.g, db = new_pal.b - pix.b;
		int new_dist = (dr * dr) + (dg * dg) + (db * db);

		if (new_dist < dist)
		{
			dist = new_dist;
			pal = PAL[i];
		}
	}

	return pal;
}

// Helper funcs for dithering
#ifdef DITHER
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
#endif

static void manipulate(bitmap_pixel_rgb_t* pixels, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// Get a pointer to the pixel and select a palette color for it.
			bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];
			bitmap_pixel_rgb_t pal = select_from_pal(*pix);
#ifdef DITHER
			// Calculate the quantization error in all components.
			int qe[] = { pix->r - pal.r, pix->g - pal.g, pix->b - pal.b };

			// Distribute the error onto the neighbours.
			apply_quant_err(pixels, width, height, x + 1, y, qe, 7);
			apply_quant_err(pixels, width, height, x - 1, y + 1, qe, 3);
			apply_quant_err(pixels, width, height, x, y + 1, qe, 5);
			apply_quant_err(pixels, width, height, x + 1, y + 1, qe, 1);
#endif
			// Assign the new pixel value.
			*pix = pal;
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
	manipulate(pixels, width, height);

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
		"sails_mod.bmp",
		BITMAP_BOOL_TRUE,
		&params,
		(bitmap_pixel_t*)pixels
	);

	assert(error == BITMAP_ERROR_SUCCESS);

	// Free the memory that has been allocated by the bitmap library.
	free(pixels);

	return 0;
}
