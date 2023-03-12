#include "PlayerController.h"
#include "../../Entity.h"

namespace Components {
	namespace Controllers { 

		Player::Player() {}

		void Player::update() {
			/*
			Vector3f& direction = owner->getComponent<Components::Velocity>()->getVel();
			Mat3 rot = getRotationXZ(-owner->getComponent<Components::Facing>()->getXZ());
			direction = Vec3MulMat3(direction, rot);
			owner->getComponent<Components::Velocity>()->setVel(direction);
			std::cout << direction << std::endl;
			*/
		}
	}
}