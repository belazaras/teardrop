#version 420 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec3 normal;
layout (location = 1) in vec2 texcoord0;

uniform mat4 mvp_matrix; 
uniform mat4 mv_matrix;

out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 UV;
} vs_out;

// Position of light
uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);

void main(void)
{
    vs_out.UV = texcoord0;

    // Calculate view-space coordinate
    vec4 P = mv_matrix * position;

    // Calculate normal in view-space
    vs_out.N = mat3(mv_matrix) * normal;

    // Calculate light vector
    vs_out.L = light_pos - P.xyz;

    // Calculate view vector
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = mvp_matrix * position;
}
