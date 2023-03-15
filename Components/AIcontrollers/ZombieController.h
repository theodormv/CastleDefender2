#pragma once

#include "../../Component.h"
#include "../../Entity.h"
#include "../VelocityComponent.h"

namespace Components {
	namespace Controllers {
		class Zombie : public Component {

			Entity* playerTarget;

		public:
			Zombie();
			Zombie(Entity* target);
			~Zombie();

			void update() override;
			void init() override;
			


			static uint16 killed;
		};

	}
}