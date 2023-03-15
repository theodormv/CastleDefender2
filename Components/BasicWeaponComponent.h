#pragma once

#include"../Component.h"
#include "../types.h"
#include "../Grafikk/Model.h"

typedef struct {
	int32 damage;
	float lifetime;
	float rateOfFire;
	Model* projectileModel;
	int projectileSize;
	float speed;
} Weapon;


namespace Components {
	class BasicWeapon : public Component {
		Weapon* weapon;

		float lastFire;
		float secondsPerShot;
		bool canFire;
	public:

		BasicWeapon() = default;
		BasicWeapon(Weapon* w);


		void update() override;
		void init() override;

		void fire();
		

	};
}