#pragma once
#include "../Game.h"
#include "../Matrix3.h"

namespace Game{
	namespace Physics {
		class MagField {
			
			Vector3f field;
			Shape* area;

		public:

			MagField() = default;
			MagField(float x, float y, float z);
			
			void rotateXZ(float rad);
			void rotateYZ(float rad);
			
			Vector3f getForce(Entity& ent);

		};

	}
}