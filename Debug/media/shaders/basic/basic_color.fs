#version 420 core

// Interpolated values from the vertex shaders
in vec2 UV;
 
// Ouput data
out vec3 color;

uniform vec3 input_color = vec3(1.0,0.5,1.0);
 
// Values that stay constant for the whole mesh.
// uniform sampler2D myTextureSampler;
 
void main(){
    color = input_color;
}