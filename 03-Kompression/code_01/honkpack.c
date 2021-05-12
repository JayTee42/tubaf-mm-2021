#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

static int read_byte(FILE* input, uint8_t* b)
{
	int result = fgetc(input);

	if (result == EOF)
	{
		if (!feof(input))
		{
			fprintf(stderr, "Failed to read from input.\n");
			exit(EXIT_FAILURE);
		}

		return 0;
	}

	*b = (uint8_t)result;
	return 1;
}

static void write_byte(FILE* output, uint8_t b)
{
	if (fputc(b, output) == EOF)
	{
		fprintf(stderr, "Failed to write to output.\n");
		exit(EXIT_FAILURE);
	}
}

typedef enum __state_t__
{
	STATE_IND,
	STATE_HOM,
	STATE_HET
} state_t;

int main(int argc, char** argv)
{
	FILE* input = stdin;
	FILE* output = stdout;

	// Init the state machine.
	uint8_t b = 0;
	size_t count = 0;
	state_t state = STATE_IND;

	while (read_byte(input, &b))
	{
		switch (state)
		{
		case STATE_IND:

			count = (size_t)(b & 0x7F); // Binary: 0b01111111
			state = (b >> 7) ? STATE_HOM : (count > 0) ? STATE_HET : STATE_IND;

			break;

		case STATE_HOM:

			for (size_t i = 0; i < count; i++)
			{
				write_byte(output, b);
			}

			state = STATE_IND;
			break;

		case STATE_HET:

			write_byte(output, b);

			if (--count == 0)
			{
				state = STATE_IND;
			}

			break;
		}
	}

	// Close the input / output stream.
	fclose(input);
	fclose(output);

	// Validate the end state.
	if (state != STATE_IND)
	{
		fprintf(stderr, "Bad format!\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
