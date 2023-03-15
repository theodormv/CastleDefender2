#include "includes.h"


namespace Game {
	Window window;
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<CompWrapper>, compNum> components;
	
	std::vector<Terrain> terrain;

	bool shouldClean = false;
	Cam*& activeCamera = Components::Model::activeCam;


	void init(const char* name, uint16 width, uint16 height) {
		updateDeltaTime();
		if (glfwInit() != 1)
			Error("Failed to initialize GLFW");



		initWindow(name, width, height);

		if (glewInit() != GLEW_OK) {
			Error("Failed to init GLEW");
		}

		int vma = 0;
		int vmi = 0;
		GlCall(glGetIntegerv(GL_MAJOR_VERSION, &vma));
		GlCall(glGetIntegerv(GL_MINOR_VERSION, &vmi));

		std::cout << "openGL version: " << vma << "." << vmi << std::endl;
	}

	void initWindow(const char* name, uint16 width, uint16 height) {
		window.name = name;
		window.width = width;
		window.height = height;

		window.context = glfwCreateWindow(width, height, name, NULL, NULL);

		if (window.context == NULL) {
			Error("Failed to init GLFW Window");
		}

		glfwMakeContextCurrent(window.context);

		GlCall(glEnable(GL_DEPTH_TEST));
	}
	
	Entity* addEntity() {

		std::unique_ptr<Entity> ent = std::move(std::make_unique<Entity>());
		entities.emplace_back(std::move(ent));
		return (entities.end() - 1)->get();
	}

	void update() {
		for (int i = 0; i < compNum; i++) {
			if (i == getCompID<Components::Model>()) continue;
			std::vector<CompWrapper>& vec = components[i];
			for (int j = 0; j < vec.size(); j++){
				if (*vec[j] == nullptr){
					continue;
				}
				vec[j]->update();

			}
		}
		updateDeltaTime();

	}

	void handleCollitions() {
		std::vector<CompWrapper>& hitboxes = components[getCompID<Components::Hitbox>()];

		for (int i = 0; i < hitboxes.size(); ++i) {
			Components::Hitbox* hitbox = reinterpret_cast<Components::Hitbox*>(hitboxes[i].getCore());

			if (hitbox == nullptr) continue; // account for nullptr

			for (int j = i + 1; j < hitboxes.size(); ++j) {

				Components::Hitbox* other = reinterpret_cast<Components::Hitbox*>(hitboxes[j].getCore());

				if (other == nullptr) continue;

				Vector3f correction = other->correctedIntersect(hitbox);


				//check collition
				if (correction.sqareMag()) {


					//check if projectiles


					if (hitbox->owner->hasComponent<Components::Projectile>()) {
						hitbox->owner->pendingDeletion = true;

						if (other->owner->hasComponent<Components::Life>()) other->owner->getComponent<Components::Life>()->getLife() -= hitbox->owner->getComponent<Components::Projectile>()->getDamage();

						continue;
					}

					if (other->owner->hasComponent<Components::Projectile>()) {
						other->owner->pendingDeletion = true;

						if (hitbox->owner->hasComponent<Components::Life>()) hitbox->owner->getComponent<Components::Life>()->getLife() -= other->owner->getComponent<Components::Projectile>()->getDamage();


						continue;
					}


					//resolve collition

					hitbox->owner->getComponent<Components::Position>()->getPos() += correction / 2;
					other->owner->getComponent<Components::Position>()->getPos() -= correction / 2;

				}


				
			}
			//std::cout << "TERRAIN" << std::endl;
			for (int j = 0; j < terrain.size(); ++j) {

				Vector3f correction = terrain[j].getShape()->correctedIntersect(hitbox);
				//std::cout << "Correction : " << correction << std::endl;
				//std::cout << "Game::handle Collitions : " << correction << std::endl;
				if (correction.get(1) && !(correction.get(0) && correction.get(2))) { //if only has a y-component check grounded

					hitbox->owner->getComponent<Components::Velocity>()->getVel()[1] = 0;
					if (correction.get(1) > 0) {
						hitbox->owner->setState(States::grounded);
					}
					
				}

				hitbox->owner->getComponent<Components::Position>()->getPos() += correction;

				if(correction.sqareMag() && hitbox->owner->hasComponent<Components::Projectile>()) {
					hitbox->owner->pendingDeletion = true;
				}
			}
			//std::cout << std::endl;
		}
	}

	bool removeComponent(Component* comp, uint16 type) {
		std::vector<CompWrapper>& comps = components[type];

		int16 index = -1;

		for (int i = 0; i < comps.size(); i++) {
			if (comps[i].getCore() == comp) {
				index = i;
				break;
			}
		}
		//std::cout << "Game::removeComponent : "<< index << std::endl;
		if (index == -1) return false;

		delete comp;
		comps[index].getCore() = nullptr;
		return true;
	}

	bool removeEntity(Entity* ent) {
		std::array<Component*, compNum>  comps = ent->getComponents();

		int index = -1;
		for (int i = 0; i < entities.size(); ++i) {
			if (entities[i].get() == ent) {
				index = i;
				break;
			}
		}

		if (index == -1) return false;

		entities.erase(entities.begin() + index);
		
		for (int i = 0; i < comps.size(); ++i) {
			if (comps[i]) {

				removeComponent(comps[i], i);
			}
		}
		//std::cout << "Removed entity : " << ent << std::endl;
		return true;
	}



	void handleStates() {
		using namespace Components;
		for (int i = 0; i < entities.size(); ++i) {

			EntityP ent = entities[i].get();

			switch (ent->getState())
			{

			case States::grounded:

		
				ent->getComponent<Velocity>()->setVel(0, 0, 0);

				if (!ent->hasComponent<Hitbox>()) break;


				{
					bool contact = false;

					Hitbox checkBox(*ent->getComponent<Hitbox>());

					checkBox.move(Physics::gravity.getNorm()*0.05);


					for (int t = 0; t < terrain.size(); ++t) {
						contact = contact || terrain[t].getShape()->checkIntersect(&checkBox);
					}
					if (!contact) ent->setState(States::falling);
				}
				

				break;
			case States::falling:
				ent->getComponent<Velocity>()->getVel() += Physics::gravity * dt;
				break;
			default:
				break;
			}

			if (entities[i]->hasComponent<Components::Position>()) {
				if (entities[i]->getComponent<Components::Position>()->getPos()[1] < -100) {
				
					entities[i]->pendingDeletion = true;
				
				}
			}
		}
	}

	void drawTerrain() {
		for (int i = 0; i < terrain.size(); ++i) {
			terrain[i].draw();
		}
	}

	void setActiveCam(Cam* cam) {
		Components::Model::activeCam = cam;
		activeCamera = Components::Model::activeCam;
	}

	void cleanDeadEnts() {
		
		for (int i = 0; i < entities.size(); ++i) {
			if (entities[i]->pendingDeletion == true) if (removeEntity(entities[i].get())) --i;
		}
	}

	void drawEnts() {
		std::vector<CompWrapper>& mods = components[getCompID<Components::Model>()];

		for (int i = 0; i < mods.size(); ++i) {
			if (mods[i].getCore())
			{
				mods[i]->update();
				
			}
			
		}
	}
	 

}