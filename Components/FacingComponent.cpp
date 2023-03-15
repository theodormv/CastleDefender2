#include "FacingComponent.h"
#include "../Entity.h"

namespace Components {

	Facing::Facing() : XZ(0), YZ(0), fac(0,0,1) {}

	Facing::Facing(float x, float y, float z) : fac(x,y,z) {
		XZ = atan2(x, z);
		YZ = atan2(y, z);
	}

	Facing::Facing(Vector3f vec) : fac(vec) {
		XZ = atan2(vec[0], vec[2]);
		YZ = atan2(vec[1], vec[2]);
	}

	Facing::Facing(float xz, float yz) : XZ(xz), YZ(yz) {
		
		fac = Vector3f(sin(-XZ) * cos(YZ), sin(-XZ) * sin(YZ), cos(-XZ));
	
	}

	void Facing::init() {}
	void Facing::update() {
		fac[0] = cos(XZ) * cos(YZ);
		fac[1] = sin(YZ);
		fac[2] = sin(XZ) * cos(YZ);
		//float yz = YZ;
		//float xz = XZ;
		//fac = Vector3f(cos(xz) * cos(yz), cos(xz) * sin(yz), sin(xz));
	
	}

	void Facing::rotateXZ(float rad) {
		XZ += rad;


	}
	void  Facing::rotateYZ(float rad) {
		YZ += rad;

		constexpr float YZlimit = 0.75;

		if (YZ > YZlimit) YZ = YZlimit;
	
		if (YZ < -YZlimit) YZ = -YZlimit;
	}

}