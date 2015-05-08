#version 420 core
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2D tMatCap;

in vec2 vN;

void main()
{
	
	color = texture2D( tMatCap, vN ).rgb;
}