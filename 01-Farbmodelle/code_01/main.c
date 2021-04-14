#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

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

	free(pixels);

	return 0;
}
