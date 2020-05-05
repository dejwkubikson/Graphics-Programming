#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	void SkyBox();

	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	void setToonLighting();
	void setGeoShader();
	void setShaderEffect();

	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;
		
	Display _gameDisplay;
	GameState _gameState;

	Shader shaderToon;
	Shader shaderSkybox;
	Shader shaderGeo;
	Shader shaderEffect;

	Mesh planet;
	Mesh asteroid1;
	//Mesh asteroid2;

	Texture skybox;
	Texture planetTex;
	Texture asteroid1Tex;
	//Texture asteroid2Tex;

	glm::mat4 modelView;

	Camera myCamera;

	float counter;
};

