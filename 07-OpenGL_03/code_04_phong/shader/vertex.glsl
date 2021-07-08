#version 410

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec4 v_normal;
layout(location = 3) in vec2 v_tex_coords;

out vec4 f_color;
out vec2 f_tex_coords;
out vec3 f_pos;
out vec3 f_normal;

// Uniforms:
uniform float angle_y;

void main()
{
    // Useful parameters for the teapot:
    float near = 1.0;
    float far = 12.0;
    float left = -1.0;
    float right = 1.0;
    float top = 1.0;
    float bottom = -1.0;

    // mat4() works column-wise!
    mat4 frustum = mat4(
        2.0 * near / (right - left),        0.0,                                0.0,                                0.0,
        0.0,                                2.0 * near / (top - bottom),        0.0,                                0.0,
        (right + left) / (right - left),    (top + bottom) / (top - bottom),    -(far + near) / (far - near),       -1.0,
        0.0,                                0.0,                                -2.0 * near * far / (far - near),   0.0
    );

    mat4 rot_y = mat4(
        cos(angle_y),       0.0,    -sin(angle_y),  0.0,
        0.0,                1.0,    0.0,            0.0,
        sin(angle_y),       0.0,    cos(angle_y),   0.0,
        0.0,                0.0,    0.0,            1.0
    );

    vec4 trans = vec4(0.0, -4.0, -7.0, 1.0);
    vec3 pos = ((rot_y * v_position) + trans).xyz; // Swizzle!

    gl_Position = frustum * vec4(pos, 1.0);

    f_color = v_color;
    f_tex_coords = v_tex_coords;
    f_pos = pos;
    f_normal = (rot_y * v_normal).xyz;
}
