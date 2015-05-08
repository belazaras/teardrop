#version 420 core
// Output 
layout (location = 0) out vec4 color;

// Input from vertex shader
in VS_OUT
{ 
	vec3 N; 
	vec3 L;
	vec3 V;
	vec2 UV;
} fs_in;

// Material properties
uniform vec3 diffuse_albedo = vec3(1.0, 0.078, 0.576);
uniform vec3 specular_albedo = vec3(1.0,0.906,0.62);
uniform float specular_power = 54.0;
uniform vec3 ambient = vec3(0.04, 0.04, 0.04);

uniform sampler2D textureInput;

void main(void)
{ 
	// Normalize the incoming N, L, and V vectors 
	vec3 N = normalize(fs_in.N); 
	vec3 L = normalize(fs_in.L); 
	vec3 V = normalize(fs_in.V);

	// Calculate R locally
	vec3 R = reflect(-L, N);

	//Nico:
	vec3 diffuse_texture = texture( textureInput, fs_in.UV ).rgb;

	// Compute the diffuse and specular components for each fragment
	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_texture;
	//vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;
	vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;
	
	// Write final color to the framebuffer
	color = vec4(ambient + diffuse + specular, 1.0);
	//color = vec4(diffuse,1.0);
}