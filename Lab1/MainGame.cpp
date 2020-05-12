#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <ctime> // used for random


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Shader* shaderToon();
	Shader* shaderSkybox();
	Shader* shaderGeo();
	Shader* shaderEffect();

	Mesh* planet();
	Mesh* asteroid1();
	//Mesh* asteroid2();

	Texture* planetTex();
	Texture* asteroid1Tex();
	//Texture* asteroid2Tex();

	srand(time(NULL)); // initializing random seed
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 

	shaderGeo.init("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom");
	shaderSkybox.init("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shaderEffect.init("..\\res\\shaderEffect.vert", "..\\res\\shaderEffect.frag");
	shaderEnvironment.init("..\\res\\shaderEnvironment.vert", "..\\res\\shaderEnvironment.frag");
	
	planet.loadModel("..\\res\\planet.obj");
	asteroid1.loadModel("..\\res\\asteroid1.obj");
	asteroid2.loadModel("..\\res\\asteroid2.obj");

	planetTex.init("..\\res\\planet_tex.jpg");
	asteroid1Tex.init("..\\res\\asteroid1_tex.jpg");
	asteroid2Tex.init("..\\res\\asteroid2_tex.jpg");

	myCamera.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	vector<std::string> faces{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	cubemapTexture = skybox.loadCubemap(faces); // Load the cubemap using faces into cubemapTextures

	float skyboxVertices[] = {
		// positions          
		-6.0f,  6.0f, -6.0f,
		-6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		-6.0f,  6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f,  6.0f
	};

	// use openGL functionality to generate and bind data into buffers
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	counter = 1.0f;
}

void MainGame::SkyBox()
{
	glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.Bind();
	shaderSkybox.setInt("skybox", 0);
	//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", myCamera.GetView());
	shaderSkybox.setMat4("projection", myCamera.GetProjection());

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default	
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::setShaderEffect()
{
	planetTex.Bind(0);

	int randInt = rand() % 100;
	float randFloat = rand() % 100;
	randFloat /= 100;

	shaderEffect.setFloat("time", counter);
	shaderEffect.setInt("randInt", randInt);
	shaderEffect.setFloat("randFloat", randFloat);

	glm::vec4 colors[] = { glm::vec4(0.3, 0.36, 0.48, 1), glm::vec4(0.16, 0.5, 0.49, 1), glm::vec4(1, 1, 1, 1) };
	for (int i = 0; i < size(colors); i++)
		shaderEffect.setVec4("colors[" + to_string(i) + "]", colors[i]);
}

void MainGame::setGeoShader()
{
	asteroid1Tex.Bind(0);

	float randX = ((float)rand() / (RAND_MAX));
	float randY = ((float)rand() / (RAND_MAX));
	float randZ = ((float)rand() / (RAND_MAX));
	// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	shaderGeo.setFloat("randColourX", randX);
	shaderGeo.setFloat("randColourY", randY);
	shaderGeo.setFloat("randColourZ", randZ);
	// Geom: uniform float time;
	shaderGeo.setFloat("time", counter);
	// Vert: uniform mat4 transform;
	shaderGeo.setMat4("transform", transform.GetModel());
}

void MainGame::setShaderEnvironment()
{
	shaderEnvironment.setMat4("model", transform.GetModel());
	shaderEnvironment.setMat4("view", myCamera.GetView());
	shaderEnvironment.setMat4("projection", myCamera.GetProjection());
	shaderEnvironment.setVec3("cameraPos", myCamera.getPos());
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);	

	shaderEffect.Bind();
	setShaderEffect();
	transform.SetPos(glm::vec3(0, 0, 0));
	transform.SetRot(glm::vec3(0, 1, -0.45));
	transform.SetScale(glm::vec3(0.4, 0.4, 0.4));
	shaderEffect.Update(transform, myCamera);
	planetTex.Bind(0);
	planet.draw();

	shaderGeo.Bind();
	transform.SetPos(glm::vec3(3 * cosf(counter), 3 * sinf(counter), 0));
	transform.SetRot(glm::vec3(0, counter * 1.5, counter));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	setGeoShader();
	shaderGeo.Update(transform, myCamera);
	asteroid1Tex.Bind(0);
	asteroid1.draw();
	
	shaderEnvironment.Bind();
	transform.SetPos(glm::vec3(3 * cosf(counter * 0.7), 0, 3 * sinf(counter * 0.7)));
	transform.SetRot(glm::vec3(counter, counter, 0));
	transform.SetScale(glm::vec3(0.0005, 0.0005, 0.0005));
	setShaderEnvironment();
	shaderEnvironment.Update(transform, myCamera);
	asteroid2Tex.Bind(0);
	asteroid2.draw();

	SkyBox();

	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 