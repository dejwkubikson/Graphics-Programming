#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

class Texture
{
public:
	Texture();

	GLuint loadCubemap(std::vector<std::string> faces);
	GLint getTexHandler() { return textureHandler; }

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName);
	~Texture();

protected:
private:

	GLuint textureHandler;
};

