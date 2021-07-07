#version 410
precision mediump float;

in lowp vec4 f_color;
in vec2 f_tex_coords;

out vec4 out_color;

uniform sampler2D tex;

void main()
{
    out_color = texture(tex, f_tex_coords) * f_color;
}
