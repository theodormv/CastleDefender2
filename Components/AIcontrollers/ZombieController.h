#pragma once

#include "../../Component.h"
#include "../../Entity.h"
#include "../VelocityComponent.h"

namespace Components {
	namespace Controllers {
		class Zombie : public Component {

			Velocity* vel;
			Entity* playerTarget;

		public:
			Zombie();
			Zombie(Entity* target);

			void update() override;
			void init() override;
			



		};

	}
}