#version 410
precision mediump float;

in lowp vec3 f_color;
out vec3 out_color;

void main()
{
    out_color = f_color;
}