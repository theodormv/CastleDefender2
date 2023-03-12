#pragma once
#include "../Component.h"
#include "../VectorNd.h"
#include "../DeltaTime.h"

namespace Components {
	class Velocity : public Component {
		Vector3f vel;

	public:
		Velocity();
		Velocity(float x, float y, float z);
		Velocity(Vector3f vec);
		Velocity(const Velocity& other);
		Velocity(Velocity&& other) noexcept;


		inline void setVel(float x, float y, float z) {
			vel.set(0, x);
			vel.set(1, y);
			vel.set(2, z);
		}
		inline void setVel(const Vector3f& data) {
			vel = data;
		}

		inline Vector3f getVelVec() const {
			return vel;
		}

		inline Vector3f& getVel() { return vel; }

		inline Vector3f accelerate(const Vector3f& other) {
			vel += other * Game::dt;
			return vel;
		}

		void update() override;
	};
}