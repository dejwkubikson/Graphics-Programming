uniform vec3 lightDir;
in vec3 normal;

// In variables
in vec2 texCoords;
uniform sampler2D image;

void main()
{
	float intensity;
	vec4 color;
	intensity = dot(lightDir,normal);

	if (intensity > 0.95)
		color = vec4(1, 1, 1, 1);
	else if (intensity > 0.75)
		color = vec4(0.9, 0.5, 0.5, 1);
	else if (intensity > 0.5)
		color = vec4(0.6, 0.3, 0.3, 1);
	else if (intensity > 0.25)
		color = vec4(0.4, 0.2, 0.2, 1);
	else
		color = vec4(0.2, 0.1, 0.1, 1);

	gl_FragColor = texture(image, texCoords) * color;
}