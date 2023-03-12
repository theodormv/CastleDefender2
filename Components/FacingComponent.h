#pragma once
#include "../Component.h"
#include "../VectorNd.h"
#include "../Matrix3.h"


namespace Components {
	class Facing : public Component {
		
		float XZ;
		float YZ;
		Vector3f fac;

	public:
		Facing();
		Facing(float x, float y, float z);
		Facing(Vector3f vec);
		Facing(float xz, float yz);

		void init() override;
		void update() override;

		inline Vector3f getVec() { return fac; }

		inline float getXZ() { return XZ; }
		inline float getYZ() { return YZ; }

		void rotateXZ(float rad);
		void rotateYZ(float rad);

	};
}