#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "includes.h"


int main(int argc, char* argv[]) {

	Game::init("test", 1600, 1200);


	
	


	ShaderSource sorc("./shaders/shader.shader");
	Shader primaryShader(sorc);
	primaryShader.Use();
	{
		int fov_location = glGetUniformLocation(primaryShader.get(), "fov");
		GlCall(glUniform1f(fov_location, 120.f));
		int Zfar_location = glGetUniformLocation(primaryShader.get(), "Zfar");
		GlCall(glUniform1f(Zfar_location, 100.f));
		int Znear_location = glGetUniformLocation(primaryShader.get(), "Znear");
		GlCall(glUniform1f(Znear_location, 0.05f));
		int aspect_location = glGetUniformLocation(primaryShader.get(), "aspectRatio");
		GlCall(glUniform1f(aspect_location, Game::window.width/Game::window.height));//(float)Game::window.height / (float)Game::window.width));

		int light_location_location = glGetUniformLocation(primaryShader.get(), "lightPos");
		GlCall(glUniform3f(light_location_location, 0.f, 0.f, 0.f));
		int light_colour_location = glGetUniformLocation(primaryShader.get(), "lightColour");
		GlCall(glUniform3f(light_colour_location, 1.f, 1.0f, 1.f));
		int sampler_location = glGetUniformLocation(primaryShader.get(), "samp");

	}


	sorc = ShaderSource("./shaders/cubemapped.shader");
	Shader cubemapShader(sorc);
	cubemapShader.Use();
	{
		int fov_location = glGetUniformLocation(cubemapShader.get(), "fov");
		GlCall(glUniform1f(fov_location, 120.f));
		int Zfar_location = glGetUniformLocation(cubemapShader.get(), "Zfar");
		GlCall(glUniform1f(Zfar_location, 100.f));
		int Znear_location = glGetUniformLocation(cubemapShader.get(), "Znear");
		GlCall(glUniform1f(Znear_location, 0.05f));
		int aspect_location = glGetUniformLocation(cubemapShader.get(), "aspectRatio");
		GlCall(glUniform1f(aspect_location, Game::window.width / Game::window.height));//(float)Game::window.height / (float)Game::window.width));

		int light_location_location = glGetUniformLocation(cubemapShader.get(), "lightPos");
		GlCall(glUniform3f(light_location_location, 0.f, 0.f, 0.f));
		int light_colour_location = glGetUniformLocation(cubemapShader.get(), "lightColour");
		GlCall(glUniform3f(light_colour_location, 1.f, 1.0f, 1.f));
		int sampler_location = glGetUniformLocation(cubemapShader.get(), "samp");

	}


	Camera cam;
	Components::Model::activeCam = &cam;

	Vertex cubeVerts[8] = { {
	 .15f,  .25f, -.15f, //0 top right front
	 .0f, .0f, .0f,
	 1.0f, 1.0f,
	},{
	-.15f,  .25f,  -.15f, //1 top left front
	 .0f, .0f, .0f,
	 0.f, 1.f
	},{
	 .15f, -.25f,  -.15f, //2 bottom right front
	 .0f, .0f, .0f,
	 1.f, 0.f
	},{
	-.15f, -.25f,  -.15f, //3 bottom left front
	 .0f, .0f, .0f,
	 0.0f, 0.0f
	},{
	 .15f,  .25f,   .15f, //4 top right back 
	 .0f, .0f, .0f,
	 1.f, 0.f
	},{
	-.15f,  .25f,   .15f, //5 top left back
	 .0f, .0f, .0f,
	 0.f, 0.f
	},{
	 .15f, -.25f,   .15f, //6 bottom right back
	 .0f, .0f, .0f,
	 0.f, 0.f
	},{
	-.15f, -.25f,   .15f,  //7 bottom left back
	.0f, .0f, .0f,
	 1.f, 0.f
	}
	};

	unsigned int CubeIndices[36] = {
		//front face
		0, 2, 3,
		0, 3, 1,
		//back face
		5, 6, 4,
		5, 7, 6,
		//left face
		1, 7, 5,
		1, 3, 7,
		//right face
		4, 6, 2,
		4, 2, 0,
		//top face
		1, 5, 4,
		1, 4, 0,
		//bottom face
		2, 6, 7,
		2, 7, 3

	};

	

	Vertex verts[5] = { {
		.0f, .0f, .25f,
		0.f, 0.0f, 0.0f,
		.0f, .0f
	},{
		.25f, .25f, -.25f,
		0.f, 0.0f, 0.0f,
		1.0f, .0f,
	},{
		-.25f, .25f, -.25f,
		0.f, 0.0f, 0.0f,
		.0f, 1.0f,
	},{
		.25f, -.25f, -.25f,
		0.f, 0.0f, 0.0f,
		1.0f, 1.0f,
	},{
		-.25f, -.25f, -.25f,
		1.0f, .0f, .0f,
		.0f, .0f,
	}
	};


	Vertex sharpVerts[5] = { {
		.0f, .0f, .1f,
		0.f, 0.0f, 0.0f,
		.0f, .0f
	},{
		.05f, .05f, -.1f,
		0.f, 0.0f, 0.0f,
		1.0f, .0f,
	},{
		-.05f, .05f, -.1f,
		0.f, 0.0f, 0.0f,
		.0f, 1.0f,
	},{
		.05f, -.05f, -.1f,
		0.f, 0.0f, 0.0f,
		1.0f, 1.0f,
	},{
		-.05f, -.05f, -.1f,
		1.0f, .0f, .0f,
		.0f, .0f,
	}
	};


	uint32 Indices[18] = {
		0,  2,  1,
		0,  4,  2,
		0,  1,  3,
		0,  3,  4,
		1,  2,  4,
		3,  1,  4,
	};

	uint32 wireframeIndices[16] = {
		0, 1,
		0, 2,
		0, 3,
		0, 4,
		1, 2,
		2, 4,
		4, 3,
		3, 1
	};

	Game::Physics::gravity = Vector3f(0, 1.f, 0);

	Texture2D zombie("./Assets/monster.jpg"); //av Justin Nichol hentet fra https://opengameart.org/content/assorted-creatures

	TextureCube floor("./Assets/floor.jpg"); //av p0ss hentet fra https://opengameart.org/content/rusted-metal-texture-pack 

	Texture2D bulletTex("./Assets/bullet.jpg");

	Terrain::tex = &floor;

	Game::terrain.reserve(1);
	Game::terrain.emplace_back(100.f, 1.f, 100.f, Vector3f(3.f, 3.f, 0.f));


	Model bullet(sharpVerts, 5, Indices, 18, &bulletTex);

	Weapon playerWep;
	playerWep.damage = 1;
	playerWep.lifetime = 5;
	playerWep.projectileModel = &bullet;
	playerWep.projectileSize = 0.05;
	playerWep.rateOfFire = 1;

	EntityP test = Game::addEntity();
	Game::EntityAddComponent<Components::Controllers::Player>(test);

	Components::Position* playerPos = Game::EntityAddComponent<Components::Position>(test, 0, -3, 0.f);

	Components::Velocity* playerVel = Game::EntityAddComponent<Components::Velocity>(test, 0.f, 0.f, 0.f);
	
	Components::Facing* playerFac = Game::EntityAddComponent<Components::Facing>(test);
	Game::EntityAddComponent<Components::Hitbox>(test, .5f, .5f, .5f);
	Components::BasicWeapon* playerGun = Game::EntityAddComponent<Components::BasicWeapon>(test, &playerWep);

	


	Game::setActiveCam(Game::EntityAddComponent<Components::Camera>(test));

	Components::Model::activeCam->program = primaryShader;

	
	EntityP z = Game::addEntity();

	Game::EntityAddComponent<Components::Position>(z, 0.f, -1.f, -5.f);
	Game::EntityAddComponent<Components::Velocity>(z, 0.f, 0.f, 0.f);
	Game::EntityAddComponent<Components::Hitbox>(z, .5f, .5f, .5f);

	Model mod(cubeVerts, 8, CubeIndices, 36, &zombie);
	Game::EntityAddComponent<Components::Model>(z, &mod);
	Game::EntityAddComponent<Components::Controllers::Zombie>(z, test);
	Game::EntityAddComponent<Components::Life>(z, 20);

	//Game::removeEntity(z);

	Input::Controller cont(GLFW_JOYSTICK_1);

	float theta = 0;
	constexpr float antiDrift = 0.1f;
	while (!glfwWindowShouldClose(Game::window.context)) {

		cont.update();

		if (abs(cont.getAx(XBOX_RIGHT_Y_AXIS)) > antiDrift)
			playerFac->rotateYZ(-cont.getAx(XBOX_RIGHT_Y_AXIS) / 100.f);


		if (abs(cont.getAx(XBOX_RIGHT_X_AXIS)) > antiDrift)
			playerFac->rotateXZ(cont.getAx(XBOX_RIGHT_X_AXIS) / 100.f);
		//if (cont.getBt(0)) __debugbreak();



		if (abs(cont.getAx(XBOX_LEFT_Y_AXIS)) > antiDrift)
			playerVel->getVel()[2] = -cont.getAx(XBOX_LEFT_Y_AXIS)*10;


		if (abs(cont.getAx(XBOX_LEFT_X_AXIS)) > antiDrift)
			playerVel->getVel()[0] = -cont.getAx(XBOX_LEFT_X_AXIS)*10;



		if (cont.getAx(XBOX_RIGHT_TRIGGER) == 1) {

			playerGun->fire();

		}



		if (cont.getBt(0) && test->getState() == States::grounded) {
			playerVel->getVel()[1] = -1;
			playerVel->owner->setState(States::falling);
		}
		
	


		theta += 0.001;
		GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GlCall(glDepthFunc(GL_LESS));
		//reinterpret_cast<Camera*>(Game::activeCamera)->rotatez(theta);
		

		
		Game::update();
		Components::Model::activeCam->program = cubemapShader;
		Game::drawTerrain();
		Components::Model::activeCam->program = primaryShader;
		Game::handleStates();
		Game::handleCollitions();
		Game::drawEnts();
		Game::cleanDeadEnts();
 		GlCall(glfwSwapBuffers(Game::window.context));

		if (Game::entities[1].get() != z) break;

		glfwPollEvents();
	}

	std::cout << "gratulerer du vant" << std::endl;
}
