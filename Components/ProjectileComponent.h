#pragma once
#include "../Component.h"
#include "../types.h"


namespace Components {
	class Projectile : public Component {

		int32 damage;
		float lifeTime;


	public:
		Projectile();
		Projectile(int32 damage, float lifTime);

		void update() override;
		void init() override;

		inline int32 getDamage () const { return damage; }
		inline float getLifetime () const  { return lifeTime; }


	};
}