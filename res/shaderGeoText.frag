//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

//Unfrom variable
uniform sampler2D image;
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;

in vec2 TexCoords; 
 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	vec4 color;
	// Alpha set to 0.5 to overlay the texture instead of replacing it
	color = vec4(randColourX,randColourY,randColourZ, 0.5);
	fragcolor = texture(image, TexCoords) * color;
}