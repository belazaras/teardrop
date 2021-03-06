#version 420 core
// Per-vertex inputs 
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 UVcoords; 
layout (location = 2) in vec3 normal;

// Matrices we’ll need 
uniform mat4 mv_matrix; 
uniform	mat4 proj_matrix;

// Position of light 
uniform vec3 light_pos = vec3(-5.5, 10.7, -5.3);

// Outputs from vertex shader
out VS_OUT
{
	vec3 N; 
	vec3 L; 
	vec3 V; 
	vec2 UV;
} vs_out;

void main(void)
{ 
	vs_out.UV = UVcoords;
	// Calculate view-space coordinate 
	vec4 P = mv_matrix * vec4(position,1);
	// Calculate normal in view-space 
	vs_out.N = mat3(mv_matrix) * normal;
	// Calculate light vector 
	vs_out.L = light_pos - P.xyz;
	// Calculate view vector 
	vs_out.V = -P.xyz;
	// Calculate the clip-space position of each vertex
	gl_Position = proj_matrix * P;
}
