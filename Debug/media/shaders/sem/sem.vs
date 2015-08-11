#version 420 core
// Entrada por vértice
layout (location = 0) in vec3 position; 
layout (location = 2) in vec3 normal;

// Matrices que usaremos
uniform mat4 MVP;  
uniform mat4 mv_matrix; 
uniform	mat4 proj_matrix;

// Salida del vertex shader
out vec2 vN;

void main()
{

	// Posición y normal normalizadas y en espacio view.
	vec3 e = normalize( vec3( mv_matrix * vec4( position, 1.0 ) ) );
	vec3 n = normalize( vec3(mv_matrix * vec4( normal, 0.0) ) );

	// Fórmula SEM.
	vec3 r = reflect( e, n );
	float m = 2. * sqrt( pow( r.x, 2. ) + pow( r.y, 2. ) + pow( r.z + 1., 2. ) );
	vN = r.xy / m + .5;

	gl_Position = MVP * vec4( position, 1);
}