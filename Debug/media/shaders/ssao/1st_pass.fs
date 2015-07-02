#version 420 core

// Output
layout (location = 0) out vec4 color;
layout (location = 1) out vec4 normal_depth;

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 UV;
} fs_in;

// Material properties
uniform vec3 ambient = vec3(0.105, 0.105, 0.105);
uniform vec3 diffuse_albedo = vec3(0.8, 0.8, 0.9);
uniform vec3 specular_albedo = vec3(0.01);
uniform float specular_power = 128.0;
uniform float shading_level = 1.0;

uniform sampler2D textureInput;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each fragment
    vec3 diffuse_texture = texture( textureInput, fs_in.UV ).rgb;

    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
    diffuse *= diffuse;
    diffuse /= 0.6;
    //vec3 diffuse = diffuse_albedo; * vec3(0.2,0.2,0.2)

    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;

    // Write final color to the framebuffer
    color = mix(vec4(0.0), vec4(ambient + diffuse + specular, 1.0), shading_level);
    normal_depth = vec4(N, fs_in.V.z);
}
