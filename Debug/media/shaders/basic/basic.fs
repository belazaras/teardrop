#version 420 core

// Interpolated values from the vertex shaders
in vec2 UV;
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
 
void main(){
    //color = vec3(1,0.549,0);
    // Output color = color of the texture at the specified UV

    color = texture( myTextureSampler, UV ).rgb;
}