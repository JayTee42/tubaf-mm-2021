#version 410
precision mediump float;

in lowp vec4 f_color;
out vec4 out_color;

void main()
{
    out_color = vec4(vec3(gl_FragCoord.z * gl_FragCoord.z), 1.0);
}
