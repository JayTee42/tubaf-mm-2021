#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dctquant.h"
#include "compress.h"
#include "decompress.h"

int main(int argc, char** argv)
{
	// Print help text:
	if (argc == 1)
	{
		printf("This help is helpful.\n");
		return -1;
	}

	// Compression or decompression?
	int compression_mode = -1;

	// Three general-purpose paths, depending on mode:
	const char* file_path1 = NULL;
	const char* file_path2 = NULL;
	const char* file_path3 = NULL;

	// Quantization factor (percent):
	int quantization_factor = -1;

	// Iterate over the input parameters:
	for (int i = 1; i < argc; i++)
	{
		// Grab the parameter:
		if (strcmp(argv[i], "-c") == 0)
		{
			// Is there already a mode setting?
			if (compression_mode != -1)
			{
				printf("Only one of the -c resp. -d options is allowed!\n");
				return -1;
			}

			// Make sure there are at least three more parameters:
			if ((argc - 1 - i) < 3)
			{
				printf("-c option needs three parameters: <input bmp> <output bmp> <output dct>\n");
				return -1;
			}

			file_path1 = argv[++i];
			file_path2 = argv[++i];
			file_path3 = argv[++i];

			compression_mode = 1;
		}
		else if (strcmp(argv[i], "-d") == 0)
		{
			// Is there already a mode setting?
			if (compression_mode != -1)
			{
				printf("Only one of the -c resp. -d options is allowed!\n");
				return -1;
			}

			// Make sure there are at least two more parameters:
			if ((argc - 1 - i) < 2)
			{
				printf("-d option needs two parameters: <input dct> <output bmp>\n");
				return -1;
			}

			file_path1 = argv[++i];
			file_path2 = argv[++i];

			compression_mode = 0;
		}
		else if (strcmp(argv[i], "-q") == 0)
		{
			// Is there already a quantization factor?
			if (quantization_factor != -1)
			{
				printf("Only one quantization factor is allowed!\n");
				return -1;
			}

			// Make sure there is at least one more parameter:
			if ((argc - 1 - i) < 1)
			{
				printf("-q option needs one parameter: <quantization factor>\n");
				return -1;
			}

			// Read the quantization factor:
			quantization_factor = atoi(argv[++i]);

			// Validate it:
			if ((quantization_factor <= 0) || (quantization_factor > 100))
			{
				printf("Quantization factor must be between 1 and 100.\n");
				return -1;
			}
		}
	}

	// Calculate the quantization factor:
	if (quantization_factor == -1)
	{
		quantization_factor = DEFAULT_QUANT_FACTOR;
	}

	// Build the quantization matrix:
	uint32_t quant_matrix[64];

	for (size_t i = 0; i < 64; i++)
	{
		// TODO: Apply the quantization factor to the default matrix!
		quant_matrix[i] = default_quant_matrix[i];
	}

	// Mode?
	if (compression_mode == -1)
	{
		printf("Please provide a -c (compress) or -d (option)!\n");
		return -1;
	}

	if (compression_mode)
	{
		// file_path1: Input path to bitmap
		// file_path2: Output path to grayscale bitmap
		// file_path3: Output path to compressed blob
		return compress(file_path1, quant_matrix, file_path2, file_path3);
	}
	else
	{
		// file_path1: Input path to compressed blob
		// file_path2: Output path to (lossy-compressed) grayscale bitmap
		return decompress(file_path1, quant_matrix, file_path2);
	}
}
