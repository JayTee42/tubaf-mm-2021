#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <emmintrin.h>
#include "bitmap.h"

struct MandelSpec {
    //image specs
    unsigned int width;
    unsigned int height;
    unsigned int depth;

    //mandel specs
    float xlim[2];
    float ylim[2];
    unsigned int iterations;
};

void mandel_basic(bitmap_pixel_rgb_t *image, const struct MandelSpec *s){
    //x and y range in the complex plane
    float xdiff = s->xlim[1] - s->xlim[0];
    float ydiff = s->ylim[1] - s->ylim[0];

    float iter_scale = 1.0f / s->iterations;
    float depth_scale = s->depth - 1;

    //iterate over all pixels in the image
    for (int y = 0; y < s->height; y++) {
        for (int x = 0; x < s->width; x++) {

            //get the real and imaginary part of c scaled by the image width and height and offset
            float cr = x * xdiff / s->width  + s->xlim[0];
            float ci = y * ydiff / s->height + s->ylim[0];

            //this will be z_n, here the initial term z0
            float zr = cr;
            float zi = ci;

            //iteration steps
            float mk = 0.0f;

            while (++mk < s->iterations) {

                //z_n+1 = z_n² + c
                float zr1 = zr * zr - zi * zi + cr;
                float zi1 = zr * zi + zr * zi + ci;

                //save z_n+1
                zr = zr1;
                zi = zi1;

                mk += 1.0f;

                //bounded and therefore part of the mandelbrot set, if |z_n+1| > 2
                if (zr * zr + zi * zi >= 4.0f)
                    break;
            }

            //mk is between 0 and s->iterations
            //scale it to fit between 0 and 1
            mk *= iter_scale;

            //damping for nicer color gradients
            mk = sqrtf(mk);

            //scale up with color depth of image
            mk *= depth_scale;

            int pixelValue = mk;
            image[y * s->width + x].r = pixelValue;
            image[y * s->width + x].g = pixelValue;
            image[y * s->width + x].b = pixelValue;
        }
    }
}


void mandel_sse2(bitmap_pixel_t *image, const struct MandelSpec *s)
{
   // TODO:
}

int main(int argc, char *argv[]){

    //default params
    unsigned int width = 1920;
    float x = -0.5;
    float y = 0.0;
    float r = 2;

    if(argc < 2){
        printf("Creating image with default parameters...\n");
        printf("Possible usage:\n");
        printf("$>./mandel 1920\t\t\t//image width\n");
        printf("$>./mandel 1920 -0.5 0.0\t//image width, middle point coordindate\n");
        printf("$>./mandel 1920 -0.5 0.0 2.0\t//image width, middle point coordindate, range around middle point\n");
    }

    if(argc == 2){
        width = atoi(argv[1]);
    }

    if(argc == 4){
        width = atoi(argv[1]);
        x = atof(argv[2]);
        y = atof(argv[3]);
    }

    if(argc == 5){
        width = atoi(argv[1]);
        x = atof(argv[2]);
        y = atof(argv[3]);
        r = atof(argv[4]);
    }

    //limits of complex plane to draw
    float xMin = x - r;
    float xMax = x + r;
    float yMin = y - 0.75 * r;
    float yMax = y + 0.75 * r;

    //get height from aspect ratio
    unsigned int height = (unsigned int)(width * 0.75);

    struct MandelSpec spec = {
        .width = width,
        .height = height,
        .depth = 256,
        .xlim = {xMin, xMax},
        .ylim = {yMin, yMax},
        .iterations = 256
    };

    bitmap_pixel_t *image = malloc(spec.width * spec.height * sizeof(bitmap_pixel_t));

    // TODO: switch with mandel_sse2!
    mandel_basic((bitmap_pixel_rgb_t*)image, &spec);

    bitmap_parameters_t params;
    memset(&params, 0, sizeof(bitmap_parameters_t));
    params.bottomUp = BITMAP_BOOL_TRUE;
    params.widthPx = width;
    params.heightPx = height;
    params.colorDepth = BITMAP_COLOR_DEPTH_32;
    params.compression = BITMAP_COMPRESSION_NONE;
    params.dibHeaderFormat = BITMAP_DIB_HEADER_INFO;

    char filename[64];
    snprintf(filename, 64, "mandel_%d_%f_%f_%f.bmp", width, x, y, r);

    switch(bitmapWritePixels(filename, BITMAP_BOOL_TRUE, &params, image)){
        case BITMAP_ERROR_SUCCESS:
            printf("Saved as %s.\n", filename);
            break;
        case BITMAP_ERROR_INVALID_PATH:
            printf("Invalid path.\n");
            break;
        case BITMAP_ERROR_INVALID_FILE_FORMAT:
            printf("Invalid file format.\n");
            break;
        case BITMAP_ERROR_IO:
            printf("IO Error.\n");
            break;
        case BITMAP_ERROR_MEMORY:
            printf("Memory error.\n");
            break;
        case BITMAP_ERROR_FILE_EXISTS:
            printf("File exists, override not allowed.\n");
            break;
    };

    return 0;
}