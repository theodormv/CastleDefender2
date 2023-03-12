#pragma once

#include "../../Component.h"
#include "../FacingComponent.h"
#include "../VelocityComponent.h"

namespace Components {
	namespace Controllers {
		class Player : public Component {
		public:
			Player();

			void update() override;
		};
	}
}