#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "includes.h"
#include <cstdlib>


#define ADDZOMBIE(x, z) ent = Game::addEntity(); \
Game::EntityAddComponent<Components::Controllers::Zombie>(ent, player);\
Game::EntityAddComponent<Components::Position>(ent, x, 15.f, z);\
Game::EntityAddComponent<Components::Velocity>(ent, 0.f, 0.f, 0.f);\
Game::EntityAddComponent<Components::Hitbox>(ent, .5f, .5f, .5f);\
Game::EntityAddComponent<Components::Model>(ent, &ZombieModel);\
Game::EntityAddComponent<Components::Life>(ent, 4);\
Game::EntityAddComponent<Components::Facing>(ent);\
Game::EntityAddComponent<Components::BasicWeapon>(ent, &ZombieWeapon)




int main(int argc, char* argv[]) {

	Game::init("test", 1600, 1200);


	//init all controllers
	getCompID<Components::Controllers::Zombie>();
	getCompID<Components::Controllers::Player>();

	

	float fov = 90.f;
	float z_far = 100;
	float z_near = 0.05;

	glm::mat4 projection = glm::perspective(fov, (float)Game::window.width / (float)Game::window.height, z_near, z_far);

	ShaderSource sorc("./shaders/newShader.shader");
	Shader primaryShader(sorc);
	primaryShader.Use();
	{
		int pro_loc = glGetUniformLocation(primaryShader.get(), "projection");
		GlCall(glUniformMatrix4fv(pro_loc, 1, GL_FALSE, &projection[0][0]))


		int light_location_location = glGetUniformLocation(primaryShader.get(), "lightPos");
		GlCall(glUniform3f(light_location_location, 0.f, 10.f, 0.f));
		int light_colour_location = glGetUniformLocation(primaryShader.get(), "lightColour");
		GlCall(glUniform3f(light_colour_location, 0.25f, .15f, .05f));
		int sampler_location = glGetUniformLocation(primaryShader.get(), "samp");

	}


	sorc = ShaderSource("./shaders/newcubemapped.shader");
	Shader cubemapShader(sorc);
	cubemapShader.Use();
	{
		int pro_loc = glGetUniformLocation(cubemapShader.get(), "projection");
		GlCall(glUniformMatrix4fv(pro_loc, 1, GL_FALSE, &projection[0][0]))

		int light_location_location = glGetUniformLocation(cubemapShader.get(), "lightPos");
		GlCall(glUniform3f(light_location_location, 0.f, 10.f, 0.f));
		int light_colour_location = glGetUniformLocation(cubemapShader.get(), "lightColour");
		GlCall(glUniform3f(light_colour_location, .25f, .15f, .05f));
		int sampler_location = glGetUniformLocation(cubemapShader.get(), "samp");

	}


	Camera cam;
	Components::Model::activeCam = &cam;

	Vertex cubeVerts[8] = { {
	 .15f,  -.25f, -.15f, //0 bottom right front
	 .0f, .0f, .0f,
	 .0f, 1.0f,
	},{
	-.15f,  -.25f,  -.15f, //1 bottom left front
	 .0f, .0f, .0f,
	 0.f, 0.f
	},{
	 .15f, .25f,  -.15f, //2 top right front
	 .0f, .0f, .0f,
	 0.f, 0.f
	},{
	-.15f, .25f,  -.15f, //3 top left front
	 .0f, .0f, .0f,
	 0.0f, 1.0f
	},{
	 .15f,  -.25f,   .15f, //4 bottom right back 
	 .0f, .0f, .0f,
	 1.f, 1.f
	},{
	-.15f,  -.25f,   .15f, //5 bottom left back
	 .0f, .0f, .0f,
	 0.f, 0.f
	},{
	 .15f, .25f,   .15f, //6 top right back
	 .0f, .0f, .0f,
	 1.f, 0.f
	},{
	-.15f, .25f,   .15f,  //7 top left back
	.0f, .0f, .0f,
	 0.f, 1.f
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
		2, 7, 3,

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
		0,  1,  2,
		0,  2,  4,
		0,  3,  1,
		0,  4,  3,
		1,  4,  2,
		3,  4,  1,
	};

	Game::Physics::gravity = Vector3f(0, -1.f, 0);

	Texture2D zombie("./Assets/monster.jpg"); //av Justin Nichol hentet fra https://opengameart.org/content/assorted-creatures

	TextureCube floor("./Assets/floor.jpg"); //av p0ss hentet fra https://opengameart.org/content/rusted-metal-texture-pack 
	TextureCube wall("./Assets/wall.jpg"); //av rubberduck hentet fra https://opengameart.org/node/19464


	Texture2D bulletTex("./Assets/bullet.jpg");

	Terrain::tex = &floor;

	

	Game::terrain.reserve(9);
	Game::terrain.emplace_back(10.f, 1.f, 10.f, Vector3f(0.f, 0.f, 0.f));
	
	Terrain::tex = &wall;


	Game::terrain.emplace_back(2.f, 5, 2.f, Vector3f(3, 2.5f, 3));
	Game::terrain.emplace_back(2.f, 5, 2.f, Vector3f(3, 2.5f, -3));
	Game::terrain.emplace_back(2.f, 5, 2.f, Vector3f(-3, 2.5f, 3));
	Game::terrain.emplace_back(2.f, 5, 2.f, Vector3f(-3, 2.5f, -3));

	Game::terrain.emplace_back(12.f, 5.f, 1.f, Vector3f(0.f, 2.5, 5.5f));
	Game::terrain.emplace_back(12.f, 5.f, 1.f, Vector3f(0.f, 2.5, -5.5f));
	Game::terrain.emplace_back(1.f, 5.f, 10.f, Vector3f(5.5f, 2.5, 0.f));
	Game::terrain.emplace_back(1.f, 5.f, 10.f, Vector3f(-5.5f, 2.5, 0.f));





	Model bullet(sharpVerts, 5, Indices, 18, &bulletTex);
	Model ZombieBullet(sharpVerts, 5, Indices, 18, &floor);

	Weapon playerWep;
	playerWep.damage = 1;
	playerWep.lifetime = 5;
	playerWep.projectileModel = &bullet;
	playerWep.projectileSize = 0.05;
	playerWep.rateOfFire = 3;
	playerWep.speed = 20;

	EntityP player = Game::addEntity();
	Game::EntityAddComponent<Components::Controllers::Player>(player);


	

	Components::Position* playerPos = Game::EntityAddComponent<Components::Position>(player, 0, 15.f, 0.f);

	Components::Velocity* playerVel = Game::EntityAddComponent<Components::Velocity>(player, 0.f, 0.f, 0.f);
	
	Components::Facing* playerFac = Game::EntityAddComponent<Components::Facing>(player);
	Game::EntityAddComponent<Components::Hitbox>(player, .5f, .5f, .5f);
	Components::BasicWeapon* playerGun = Game::EntityAddComponent<Components::BasicWeapon>(player, &playerWep);
	Game::EntityAddComponent<Components::Life>(player, 1);


	Game::setActiveCam(Game::EntityAddComponent<Components::Camera>(player));

	Components::Model::activeCam->program = primaryShader;


	Weapon ZombieWeapon;
	ZombieWeapon.damage = 1;
	ZombieWeapon.lifetime = 10;
	ZombieWeapon.projectileModel = &ZombieBullet;
	ZombieWeapon.projectileSize = 0.05;
	ZombieWeapon.rateOfFire = 1.f/3.f;
	ZombieWeapon.speed = 5;

	Model ZombieModel(cubeVerts, 8, CubeIndices, 36, &zombie);
	Entity* ent;
	ADDZOMBIE(0, 3);
	ADDZOMBIE(0, -3);
	ADDZOMBIE(3, 0);
	ADDZOMBIE(-3, 0);
	

	//Game::removeEntity(z);

	Input::Controller cont(GLFW_JOYSTICK_1);

	float theta = 0;
	constexpr float antiDrift = 0.1f;


	float spawnCounter = 5;
	int pos = 0;

	while (!glfwWindowShouldClose(Game::window.context)) {


		if (spawnCounter < 0) {
			spawnCounter = 5;
			switch (pos)
			{
			case 0:
				ADDZOMBIE(3, 3);
				break;
			case 1:
				ADDZOMBIE(3, -3);
				break;
			case 2:
				ADDZOMBIE(-3, 3);
				break;
			case 3:
				ADDZOMBIE(-3, -3);
				break;
			default:
				break;
			}



			pos = ++pos % 4;
		}

		spawnCounter -= Game::dt;

		cont.update();

		//playerFac->setXZ(PI);
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



		if (cont.getBt(0) && player->getState() == States::grounded) {
			playerVel->getVel()[1] = 1 ;
			player->setState(States::falling);
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

		//std::cout << "position: " << playerPos->getPos() << std::endl;

		bool playerAlive = false;
		for (int i = 0; i < Game::entities.size(); ++i) {
			if (Game::entities[i].get() == player) {
				playerAlive = true;
			}
		}

		if (!playerAlive) {

			std::cout << "Du dode!";
			break;
		}

		if (playerAlive && Game::entities.size() == 1) {
			std::cout << "Gratulerer du vant!";
			break;
		}
		

		glfwPollEvents();
	}

	std::cout << " Du drepte hele " << Components::Controllers::Zombie::killed << " zombie(r), WOW!" << std::endl;

}
