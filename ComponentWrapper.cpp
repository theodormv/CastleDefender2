#include "ComponentWrapper.h"

CompWrapper::CompWrapper(Comp_Ptr* comp) : data(comp) {

}

//CompWrapper::CompWrapper(Comp_Ptr& comp) : data(&comp) {}

CompWrapper::CompWrapper(CompWrapper&& other) noexcept : data(other.data) { other.data = nullptr; }

CompWrapper::CompWrapper(const CompWrapper& other) : data(other.data) {}


Component*& CompWrapper::operator * () {
	return *data;
}


Component* CompWrapper::operator -> () {
	return *data;
}

Component** CompWrapper::operator = (Comp_Ptr& other) {
	data = &other;
	return data;
}

Component** CompWrapper::operator = (Comp_Ptr* other) {
	data = other;
	return data;
}

Component*& CompWrapper::getCore() {
	//std::cout << data << ", " << *data << std::endl;
	return *data;
}