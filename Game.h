#pragma once
#include "Entity.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "types.h"
#include "Error.h"
#include "ComponentWrapper.h"
#include "Grafikk/Camera.h"
#include "Grafikk/Shader.h"
#include "Component.h"
#include "Input/Controller.h"
#include "Terrain/terrain.h"
#include "DeltaTime.h"
#include "Physics/Gravity.h"


namespace Game {
	extern Window window;
	extern std::vector<std::unique_ptr<Entity>> entities;
	extern std::array<std::vector<CompWrapper>, compNum> components;

	extern std::vector<Terrain> terrain;
	extern float dt;
	extern bool shouldClean;
	extern Cam*& activeCamera;


	void init(const char* name, uint16 width, uint16 height);
	void initWindow(const char* name, uint16 width, uint16 height);
	

	Entity* addEntity();
	
	template<typename T>
	T* addComponent(T* comp) {
		components[getCompID<T>()].emplace_back(comp);
	}

	template<typename T, typename ... Targs>
	T* EntityAddComponent(Entity* ent, Targs ... Margs) {
		T** comp = new T*;
		*comp = new T(std::forward<Targs>(Margs)...);
		(*comp)->owner = ent;
		(*comp)->init();
		//std::cout << "component address: "<< comp << std::endl;
		ent->addComponent(*comp);

		std::vector<CompWrapper>& wrapVec = components[getCompID<T>()];

		//find a place to insert
		CompWrapper* insertionLocation = nullptr;

		for (int i = 0; i < wrapVec.size(); i++) {
			if (*wrapVec[i] == nullptr){
				insertionLocation = &wrapVec[i];
				break;
			}
		}
		
		if (insertionLocation) *insertionLocation->data = (Component*)*comp;
		else wrapVec.push_back(CompWrapper((Component**)comp));

		return *comp;
	}


	bool removeComponent(Component* comp, uint16 type);

	bool removeEntity(Entity* ent);

	template<typename T>
	bool EntityRemoveComponent(Entity* ent) {
		Component* target = ent->getComponent<T>(); 
		
		std::vector<CompWrapper>& vec = components[getCompID<T>()];
		for (int i = 0; i < vec.size(); i++) if (*vec[i] == target) *vec[i] = nullptr;
	
		return ent->removeComponent<T>();
	}

	void update();

	void handleCollitions();

	void drawTerrain();

	void setActiveCam(Cam* cam);

	void handleStates();

	void cleanDeadEnts();

	void drawEnts();

	void quit(); //terminate glew, glfw, delete all components
	//first delete all entities then all component => entity destructor does not delete components, needs separate function
}