#pragma once

class Entity;

class Component {
public:
	Entity* owner;
	Component() : owner(nullptr) {};
	~Component() {};


	virtual void init() {};
	virtual void update() = 0;


};


