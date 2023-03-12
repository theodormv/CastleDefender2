#include "VelocityComponent.h"
#include "../Entity.h"
#include "PositionComponent.h"
#include "FacingComponent.h"
#include "./AIcontrollers/PlayerController.h"

namespace Components {
	Velocity::Velocity() {}

	Velocity::Velocity(float x, float y, float z) : vel(x,y,z) {}
	Velocity::Velocity(Vector3f vec) : vel(vec) { std::cout << "Velocity Component : " << vel << std::endl; }
	Velocity::Velocity(const Velocity& other) : vel(other.vel) {}
	Velocity::Velocity(Velocity&& other) noexcept : vel(other.vel) {}

	void Velocity::update() {
		Vector3f direction = owner->getComponent<Components::Velocity>()->getVel();


		if (owner->hasComponent<Components::Controllers::Player>()) {
			Mat3 rot = getRotationXZ(-owner->getComponent<Components::Facing>()->getXZ());
			direction = Vec3MulMat3(direction, rot);
		}
		

		owner->getComponent<Position>()->getPos() += direction * Game::dt;
	}
}