#include "ZombieController.h"
//#include "../../Entity.h
#include "../PositionComponent.h"
#include "../FacingComponent.h"
#include "../BasicWeaponComponent.h"


namespace Components {
	namespace Controllers {

		uint16 Zombie::killed = 0;

		Zombie::Zombie() : playerTarget(nullptr) {};
		Zombie::Zombie(Entity* target) : playerTarget(target){};

		Zombie::~Zombie() {
			++killed;
			//std::cout << "Killed Zombie: " << killed << std::endl;
		}

		void Zombie::init() {}


		void Zombie::update() {
			if (!playerTarget || owner->getState() != States::grounded) return;

			
			Vector3f dist = playerTarget->getComponent<Position>()->getPos() - owner->getComponent<Position>()->getPos();
			dist[1] = 0;
			owner->getComponent<Components::Facing>()->setXZ(-(atan2(dist[0], dist[2]) - PI/2));

			owner->getComponent<Components::BasicWeapon>()->fire();



			if (dist.sqareMag() < 1) return;
			
			owner->getComponent<Components::Velocity>()->getVel()[0] = dist[0];
			owner->getComponent<Components::Velocity>()->getVel()[2] = dist[2];




			//owner->getComponent<Components::Facing>()->setXZ(atan2(dist[0], dist[2]) + PI);


			//std::cout << "Zombie Controller : update " << owner->getComponent<Components::Velocity>()->getVel() << std::endl;


		}


	}
}