#version 410
precision mediump float;

// Input:
in highp vec2 c;

// Output:
out vec4 out_color;

#define MAX_ITERATIONS 200u

void main()
{
	// Iterate:
	highp vec2 z = c;

	for (uint i = 0u; i < MAX_ITERATIONS; i++)
	{
		// Test if we have left the circle with radius 2:
		if (dot(z, z) > 4.0)
		{
			out_color = vec4(1.0, 1.0, 1.0, 1.0);
			return;
		}

		// Calculate the next element of the sequence:
		z = vec2((z.x * z.x) - (z.y * z.y), 2.0 * z.x * z.y) + c;
	}

	out_color = vec4(0.0, 0.0, 0.0, 1.0);
}
