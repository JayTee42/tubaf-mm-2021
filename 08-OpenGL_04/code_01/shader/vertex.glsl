#version 410
layout(location = 0) in vec4 v_position;

// Uniforms:
uniform vec2 g_position;
uniform vec2 g_half_frame;

// Output:
out vec2 c;

void main()
{
	gl_Position = v_position;
	c = g_position + (v_position.xy * g_half_frame);
}
