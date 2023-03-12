#include "CameraComponent.h"
#include "../Entity.h"
#include "FacingComponent.h"
#include "PositionComponent.h"
namespace Components {

	Camera::Camera() {}
	
	void Camera::init() {
		update();
	}

	void Camera::update() {

		position = owner->getComponent<Position>()->getPos();

		if (owner->hasComponent<Facing>()) {
			Facing* fac = owner->getComponent<Facing>();

			rotx = -fac->getYZ();
			roty = -fac->getXZ();

		}
	}


}
