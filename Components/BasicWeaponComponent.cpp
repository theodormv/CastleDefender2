#include "BasicWeaponComponent.h"
#include "../Game.h"
#include "FacingComponent.h"
#include "ProjectileComponent.h"
#include "VelocityComponent.h"
#include  "PositionComponent.h"
#include "HitboxComponent.h"
#include "ModelComponent.h"

namespace Components {
	BasicWeapon::BasicWeapon(Weapon* w) : weapon(w), lastFire(0), canFire(false), secondsPerShot(1/w->rateOfFire) {}



	void BasicWeapon::update() {
		lastFire += Game::dt;
		if (lastFire > secondsPerShot) {
			canFire = true;
		}
	}

	void BasicWeapon::init() {}

	void BasicWeapon::fire() {
		if (!canFire) return;
		canFire = false;
		lastFire = 0;

		Entity* shot = Game::addEntity();

		Vector3f spawnPos = owner->getComponent<Components::Position>()->getPos();

		spawnPos += owner->getComponent<Components::Facing>()->getVec() * sqrt(3 * (weapon->projectileSize / 2) * (weapon->projectileSize / 2));

		spawnPos += owner->getComponent<Components::Facing>()->getVec() * owner->getComponent<Components::Hitbox>()->getFurthestPoint().mag();

		Vector3f facing = owner->getComponent<Components::Facing>()->getVec();

		//std::cout << facing << " " << owner->getComponent<Components::Facing>()->getXZ() << " " << owner->getComponent<Components::Facing>()->getYZ() << std::endl;

		Game::EntityAddComponent<Components::Position>(shot, spawnPos);
		Game::EntityAddComponent<Components::Facing>(shot, facing);
		Game::EntityAddComponent<Components::Projectile>(shot, weapon->damage, weapon->lifetime);
		Game::EntityAddComponent<Components::Velocity>(shot, owner->getComponent<Components::Velocity>()->getVel() + facing*50);
		Game::EntityAddComponent<Components::Hitbox>(shot, weapon->projectileSize, weapon->projectileSize, weapon->projectileSize);
		Game::EntityAddComponent<Components::Model>(shot, weapon->projectileModel);
	}



}