#include "VelocityComponent.h"
#include "../Entity.h"
#include "PositionComponent.h"
#include "FacingComponent.h"
#include "./AIcontrollers/PlayerController.h"

namespace Components {
	Velocity::Velocity() {}

	Velocity::Velocity(float x, float y, float z) : vel(x,y,z) {}
	Velocity::Velocity(Vector3f vec) : vel(vec) {}
	Velocity::Velocity(const Velocity& other) : vel(other.vel) {}
	Velocity::Velocity(Velocity&& other) noexcept : vel(other.vel) {}

	void Velocity::update() {
		Vector3f direction = vel;


		if (owner->hasComponent<Components::Controllers::Player>()) {
			Mat3 rot = getRotationXZ(-owner->getComponent<Components::Facing>()->getXZ() + PI/2);
			direction = Vec3MulMat3(direction, rot);
		}
		
		//std::cout << vel << std::endl,
		owner->getComponent<Position>()->getPos() += direction * Game::dt;
	}
}