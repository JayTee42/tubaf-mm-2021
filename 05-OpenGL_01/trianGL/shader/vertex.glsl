#version 410
layout(location = 0) in vec4 v_position;
layout(location = 1) in vec3 v_color;

out vec3 f_color;

void main()
{
    gl_Position = v_position;
    f_color = v_color;
}