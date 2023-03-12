#include "ZombieController.h"
//#include "../../Entity.h
#include "../PositionComponent.h"

namespace Components {
	namespace Controllers {

		Zombie::Zombie() : playerTarget(nullptr) {};
		Zombie::Zombie(Entity* target) : playerTarget(target), vel() {};

		void Zombie::init() {
			vel = owner->getComponent<Velocity>();
		}


		void Zombie::update() {
			if (!playerTarget) return;

			Vector3f dist = playerTarget->getComponent<Position>()->getPos() - owner->getComponent<Position>()->getPos();
			dist[1] = 0;

			if (dist.sqareMag() < 1) return;
			vel->getVel()[0] = dist[0];
			vel->getVel()[2] = dist[2];

			//std::cout << "Zombie Controller : update " << vel->getVel() << std::endl;


		}


	}
}