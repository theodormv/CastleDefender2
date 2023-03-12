#include "HitboxComponent.h"
#include "../Entity.h"

namespace Components {
	Hitbox::Hitbox(float height, float width, float depth) : BoxCore(height, width, depth) {}

	Hitbox::Hitbox(const Hitbox& other) : BoxCore(other) {}

	Hitbox::~Hitbox() {}

	void Hitbox::init() {
		center = &owner->getComponent<Position>()->getPos();
	}

	void Hitbox::update() {}

}