#include "ComponentPtr.h"


Comp_Ptr::Comp_Ptr(Component*&& component) {
	data = component;
}
Comp_Ptr::~Comp_Ptr() {
	delete data;
}

Component& Comp_Ptr::operator * () {
	return *data;
}

Component* Comp_Ptr::operator -> () {
	return data;
}

Component* Comp_Ptr::destory() {
	delete data;
	data = nullptr;
}

bool Comp_Ptr::operator == (Component* other) {
	return data = other;
}

bool Comp_Ptr::operator == (Comp_Ptr& other) {
	return data == other.data;
}