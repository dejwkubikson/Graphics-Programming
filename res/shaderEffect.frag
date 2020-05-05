#version 400
// Layout Qualifers
layout( location = 0 ) out vec4 fragColor;

// In qualifers
in vec2 texCoords;
in vec3 normal;
in vec3 position;
in float timer;

// Uniform qualifers
uniform sampler2D image;
uniform vec4 colors[3];
uniform int randInt;
uniform float randFloat;

// Other qualifers
int indexColor = 0;
float colorLine = 0.0f;
vec4 currCol = vec4(0, 0, 0, 0);
vec4 nextCol = vec4(0, 0, 0, 0);
vec4 showCol = vec4(0, 0, 0, 0);

void main()
{
	// Getting the index of the current colour
	indexColor = int(mod(timer, colors.length()));

	// Assigning the current colour	
	currCol = colors[indexColor];
	
	// Checking which colour is next
	if(indexColor == colors.length() - 1)
		nextCol = colors[0];
	else
		nextCol = colors[indexColor + 1];

	// Getting value of the colour line
	colorLine = dot(vec3(0, 1, 0), vec3(texCoords, 0));

	// Drawing colour line between the two colours (current and next)
	if(fract(timer) > colorLine - 0.01f && fract(timer) < colorLine + 0.01f)
		showCol = vec4(0, 0, 0, 1);
	else
		if(fract(timer) > colorLine)
			showCol = nextCol;
		else
			showCol = currCol;

	// Getting value of the vertical and horizontal lines
	float vertLine = dot(vec3(0, 1, 0), normal);
	float horiLine = dot(vec3(1, 0, 0), normal);

	// 25% chance - drawing the 'storm' effect
	if(randInt < 25 && ((vertLine > randFloat - 0.012f && vertLine < randFloat + 0.012f) || (horiLine > randFloat - 0.012f && horiLine < randFloat + 0.012f)))
		showCol = vec4(1, 1, 0, 1);

	// Assigning texture coordinates
	vec2 coords = texCoords;

	// Calculating the sine and cosine values, multiplying by 0.8 to get rid of texture edges when rotating
	float sinVal = sin(timer) * 0.8f;
	float cosVal = cos(timer) * 0.8f;

	// Moving to origin
	coords -= vec2(0.5f, 0.5f);

	// Creating rotation matrix
	mat2 rotate = mat2( vec2(sinVal, -cosVal),
						vec2(cosVal,  sinVal) );
	
	// Rotating
	coords *= rotate;

	// Moving back to the same place
	coords += vec2(0.5f, 0.5f);

	// Returning colour of the pixel.
	fragColor = texture2D(image, coords) * showCol;
}