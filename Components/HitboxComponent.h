#pragma once
#include "../Component.h"
#include "PositionComponent.h"
#include "../Shapes/boxcore.h"

namespace Components {
	class Hitbox : public Component, public BoxCore {

	public:

		Hitbox() = default;
		Hitbox(float height, float width, float depth);
		Hitbox(const Hitbox& other);
		~Hitbox();

		void init() override;
		void update() override;


		inline void move(const Vector3f& vec) { *center += vec; }
		//bool checkIntersectRay(const Vector3f& dir, const Vector3f& origin) const;
		//bool checkIntersectSegment(const Vector3f& segm, const Vector3f& origin) const;

	};
} 