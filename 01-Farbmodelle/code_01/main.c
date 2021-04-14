#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

void manipulate(bitmap_pixel_rgb_t* pixels, int count)
{
	for (int i = 0; i < count; i++)
	{
		// TODO
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
	printf("Bitmap dimensions: %d x %d\n", width, height);

	// Manipulate the pixels.
	manipulate(pixels, width * height);

	// Write the pixels back.
	bitmap_parameters_t params =
	{
		// Is this bitmap bottom-up?
		.bottomUp = BITMAP_BOOL_TRUE,

		// Width in pixels:
		.widthPx = width,

		// Height in pixels:
		.heightPx = height,

		// Which color depth is used?
		.colorDepth = BITMAP_COLOR_DEPTH_24,

		// Which compression is used?
		.compression = BITMAP_COMPRESSION_NONE,

		// Which kind of DIB header is used?
		.dibHeaderFormat = BITMAP_DIB_HEADER_INFO,

		// The color space the user provides:
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
