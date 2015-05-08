#version 420 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec3 normal;
//layout (location = 3) in vec3 tangent;
layout (location = 1) in vec2 texcoord0;

out VS_OUT
{
    vec3    ws_coords;
    vec3    normal;
    vec3    tangent;
    vec2    texcoord0;
    flat uint    material_id;
} vs_out;

// layout (std140) uniform transforms
// {
//     mat4        mvp_matrix;
//     mat4        model_matrix;
// };

uniform mat4 mvp_matrix; 
uniform mat4 model_matrix;

void main(void)
{
    vec3 tangent = vec3(1.0);
    gl_Position = mvp_matrix * position;
    vs_out.ws_coords = (model_matrix * position).xyz;
    vs_out.normal = mat3(model_matrix) * normal;
    vs_out.tangent = tangent;
    vs_out.texcoord0 = texcoord0;
    vs_out.material_id = uint(gl_InstanceID);
}
