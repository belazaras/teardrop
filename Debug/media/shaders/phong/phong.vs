#version 420 core
// Entrada por vértice
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

// Matrices que usaremos
uniform mat4 mv_matrix; 
uniform	mat4 proj_matrix;

// Posición de la luz 
uniform vec3 light_pos = vec3(0.0, 0.0, 0.0);

// Salida del vertex shader
out VS_OUT
{
	vec3 N; 
	vec3 L; 
	vec3 V; 
} vs_out;

void main(void)
{ 
	// Calcula coordenadas en espacio view
	vec4 P = mv_matrix * vec4(position,1);
	// Calcula la normal en view-space
	vs_out.N = mat3(mv_matrix) * normal;
	// Calcula el vector de la luz
	vs_out.L = light_pos - P.xyz;
	// Calcula el vector de la vista
	vs_out.V = -P.xyz;
	// Calcula la posición en clip-space de cada vértice
	gl_Position = proj_matrix * P;
}