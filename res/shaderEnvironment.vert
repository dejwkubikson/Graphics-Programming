#version 400
// Layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

// Uniform qualifers
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Out qualifers
out vec3 normal;
out vec3 position;

void main()
{
    normal = mat3(transpose(inverse(model))) * VertexNormal;
    position = VertexPosition;

    gl_Position = projection * view * model * vec4(VertexPosition, 1.0);
}  