#pragma once
#include <vector>
#include <bitset>
#include <memory>
#include <array>
#include "Error.h"
#include "types.h"

constexpr std::size_t compNum = 32;

enum class States {
	grounded,
	falling,
};


inline std::size_t NewCompID() {
	static std::size_t i = 0;
	if (i >= compNum) Error("More ids than components");
	return i++;
}

template<typename T> 
std::size_t getCompID(){
	static std::size_t id = NewCompID();
	return id;
}

#include "Component.h"


class Entity {

	std::array<Component*, compNum> components;

	States state;

public:
	Entity() {
		for (int i = 0; i < compNum; i++) {
			components[i] = nullptr;
		}
		state = States::falling;

		pendingDeletion = false;
	}
	

	template<typename T, typename ... Targs>
	T* addComponent(Targs ... Margs) {
		T* comp = new T(std::forward<Targs>(Margs)...);
		comp->owner = this;
		comp->init();
		components[getCompID<T>()] = comp;
		//Game::addComponent<T>(comp);
		return comp;
	}

	template<typename T>
	T* addComponent(T* comp) {
		components[getCompID<T>()] = comp;
		return comp;
	}

	bool removeComponent(Component* comp) {
		for (uint32 i = 0; i < components.size(); i++) {
			if (components[i] == comp) {
				delete components[i];
				components[i] = nullptr;
			}
		}
		return true;
	}

	template<typename T>
	bool removeComponent() {
		int i = getCompID<T>();
		delete components[i];
		components[i] = nullptr;
		//containsComponent[i] = false;
		return true;
	}

	template<typename T>
	T* getComponent() {
		return static_cast<T*>(components[getCompID<T>()]);
	}

	template<typename T>
	bool hasComponent() {
		return components[getCompID<T>()];
	}

	inline States getState() { return state; }
	inline void setState(States s) { state = s; }

	inline std::array<Component*, compNum> getComponents() { return components; }

	bool pendingDeletion;

};

typedef Entity* EntityP;

#include "./Component.h"
