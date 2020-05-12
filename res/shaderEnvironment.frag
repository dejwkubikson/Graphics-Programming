#version 400
// Layout Qualifers
layout(location = 0) out vec4 fragColor;

// Uniform qualifers
uniform vec3 cameraPos;
uniform samplerCube skybox;

// In qualifers
in vec3 normal;
in vec3 position;

void main()
{             
    vec3 pos = normalize(position - cameraPos);
    vec3 ref = reflect(pos, normalize(normal));

    fragColor = vec4(texture(skybox, ref).rgb, 1.0);
}