#include "Magnetfelt.h"


namespace Game {
	namespace Physics {
		MagField ::MagField(float x, float y, float z) : field(x,y,z) {}

		void MagField::rotateXZ(float rad) {
			field = Vec3MulMat3(field, getRotationXZ(rad));
		}

		void MagField::rotateYZ(float rad) {
			field = Vec3MulMat3(field, getRotationYZ(rad));
		}

		Vector3f MagField::getForce(Entity& ent) {

			if (ent.hasComponent<Components::Charge>() && ent.hasComponent<Components::Velocity>()) goto returnPart;

			if (area == nullptr) goto returnPart;
			
			if (area.check()) goto returnPart;
			

			return Vector3f(0, 0, 0);
		
		returnPart:
				
			return ent.getComponent<Components::Charge>()->getCharge() * cross(ent.getComponent<Components::Velocity>()->getVel(), field);
		}

	}
}