#pragma once
#include <iostream>
class Entity;

class Component {
public:
	Entity* owner;
	Component() : owner(nullptr) {};
	virtual ~Component() {}


	virtual void init() {};
	virtual void update() = 0;


};


