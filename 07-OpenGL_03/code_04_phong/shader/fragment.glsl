#version 410
precision mediump float;

in lowp vec4 f_color;
in vec2 f_tex_coords;
in vec3 f_pos;
in vec3 f_normal;

out vec4 out_color;

uniform sampler2D tex;

void main()
{
    // Normalize the normal vector.
    // We cannot do that in the vertex shader (as we did earlier)
    // because the interpolation based on three normalized vectors
    // is generally not normalized.
    vec3 normal = normalize(f_normal);

    // Position of the light source:
    vec3 light_pos = vec3(0.0, 0.0, 10.0);

    // Precalculate all vectors we need:
    vec3 light_dir = normalize(light_pos - f_pos);
    vec3 view_dir = normalize(-f_pos);
    vec3 reflect_dir = reflect(-light_dir, normal);

    // Ambient:
    vec3 i_amb = vec3(0.3);

    // Diffuse:
    vec3 i_diff = max(vec3(0.4) * dot(normal, light_dir), 0.1);

    // Specular:
    vec3 i_spec = vec3(1.0) * pow(max(dot(reflect_dir, view_dir), 0.0), 32);

    // Combine everything:
    out_color = texture(tex, f_tex_coords) * f_color * vec4(i_amb + i_diff + i_spec, 1.0);
}
