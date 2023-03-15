#include "CameraComponent.h"
#include "../Entity.h"
#include "FacingComponent.h"
#include "PositionComponent.h"
namespace Components {

	Camera::Camera() {}
	
	void Camera::init() {
		delete position;
		position = &owner->getComponent<Components::Position>()->getPos();
		Direction = owner->getComponent<Components::Facing>()->getVec();
	}

	void Camera::update() {
		Direction = owner->getComponent<Components::Facing>()->getVec();

		//program.Use();
		//setViewMatrix();
	}


}