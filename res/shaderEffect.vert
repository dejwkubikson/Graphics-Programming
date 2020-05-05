#version 400
// Layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

// Uniform qualifers
uniform mat4 transform;
uniform float time;

// Out qualifers
out vec2 texCoords;
out vec3 normal;
out vec3 position;
out float timer;

float random()
{
    return fract(sin(dot(position.xy, vec2(10.289, 59.354))) * 34384.84723 * timer / 10000);
}

void main()
{
    // Assigning data to out the variables.
	texCoords = VertexTexCoord;
    normal = VertexNormal;
    position = VertexPosition;
    timer = time;
    
    // Creating a new position for the vertices
    vec3 newPos = position + normal * random();

    // Multiplying the new position with the transform to get new position of the vertices.
    gl_Position = transform * vec4(newPos, 1);
}
