#version 410

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec4 v_color;

out vec4 f_color;

// Uniforms:
uniform float angle_y;

void main()
{
    // Useful parameters for the teapot:
    float near = 1.0;
    float far = 12.0;
    float left = -2.0;
    float right = 2.0;
    float bottom = -2.0;
    float top = 2.0;

    // mat4() works column-wise!
    mat4 frustum = mat4(
        2.0 * near / (right - left), 0.0, 0.0, 0.0,
        0.0, 2.0 * near / (top - bottom), 0.0, 0.0,
        (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1.0,
        0.0, 0.0, -2.0 * near * far / (far - near), 0.0
    );

    mat4 rot_y = mat4(
        cos(angle_y), 0.0, -sin(angle_y), 0.0,
        0.0, 1.0, 0.0, 0.0,
        sin(angle_y), 0.0, cos(angle_y), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    // Additional translation (world space):
    vec4 trans = vec4(0.0, -3.0, -6.0, 1.0);

    gl_Position = frustum * ((rot_y * v_position) + trans);
    f_color = v_color;
}
