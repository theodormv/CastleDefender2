#include "ProjectileComponent.h"
#include "../DeltaTime.h"
#include "../Entity.h"
namespace Components {

	Projectile::Projectile() : damage(0), lifeTime(1) {}

	Projectile::Projectile(int32 d, float l) : damage(d), lifeTime(l) {}


	void Projectile::update() {
		lifeTime -= Game::dt;
		if (lifeTime < 0 || owner->getState() == States::grounded) {
			owner->pendingDeletion = true;
		}
	}

	void Projectile::init() {}



}