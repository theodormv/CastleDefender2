#include "LifeComponent.h"
#include "../Entity.h"

namespace Components {

	Life::Life(int32 l) : life(l) {}


	void Life::update() {

		if (life < 0) owner->pendingDeletion = true;

	}

	void Life::init() {}



}