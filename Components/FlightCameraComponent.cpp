#include "CameraComponent.h"
#include "../Entity.h"

namespace Components {
	FlightCamera::FlightCamera() : pos(nullptr), roll(nullptr), fac(nullptr) {}

	void FlightCamera::init() {
		pos = owner->getComponent<Position>();
		roll = owner->getComponent<Roll>();
		fac = owner->getComponent<Facing>();
	}

	void FlightCamera::update() {}

	void FlightCamera::Draw(::Model& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz) {
		/*Vector3f renderPos = in_position - pos->getPos();
		//std::cout << renderPos << std::endl;

		program.Use();

		float rotx = fac->getPitch();
		float roty = fac->getYaw();
		float rotz = roll->getRoll();

		GlCall(int camRot_loc = glGetUniformLocation(program.get(), "cameraRotation"));
		GlCall(glUniform3f(camRot_loc, rotx, roty, rotz));

		Mat3 Mrotx = { 1, 0, 0,
					  0, cos(rotx), -sin(rotx),
					  0, sin(rotx), cos(rotx) };

		Mat3 Mroty = { cos(roty), 0, sin(roty),
					   0, 1, 0,
					  -sin(roty), 0, cos(roty) };

		Mat3 Mrotz = { cos(rotz), -sin(rotz), 0,
					  sin(rotz), cos(rotz), 0,
					  0, 0, 1 };

		renderPos = Vec3MulMat3(renderPos, Mrotx);
		renderPos = Vec3MulMat3(renderPos, Mroty);
		renderPos = Vec3MulMat3(renderPos, Mrotz);

		target.Draw(renderPos, in_rotx, in_roty, in_rotz, program.get());*/
	}


	void FlightCamera::Draw(::Model& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz, const Vector3f& axRoll, const Vector3f& axPitch, const Vector3f& axYaw) {
		/*Vector3f renderPos = in_position - pos->getPos();
		//std::cout << renderPos << std::endl;
	
		float rotx = fac->getPitch();
		float roty = fac->getYaw();
		float rotz = roll->getRoll();

		program.Use();

		GlCall(int modRot_loc = glGetUniformLocation(program.get(), "modelRotation"));
		GlCall(glUniform3f(modRot_loc, in_rotx, in_roty, in_rotz));

		GlCall(int camRot_loc = glGetUniformLocation(program.get(), "cameraRotation"));
		GlCall(glUniform3f(camRot_loc, fac->getPitch(), fac->getYaw(), roll->getRoll()));


		GlCall(int AxRoll_loc = glGetUniformLocation(program.get(), "modelAxisRoll"));
		GlCall(glUniform3f(AxRoll_loc, axRoll.get(0), axRoll.get(1), axRoll.get(2)));

		Vector3f AxisPitch = Vec3MulMat3(axPitch, getRotationXY(in_rotz));
		Vector3f AxisYaw = Vec3MulMat3(axYaw, getRotationXY(in_rotz));



		GlCall(int AxPitch_loc = glGetUniformLocation(program.get(), "modelAxisPitch"));
		GlCall(glUniform3f(AxPitch_loc, AxisPitch.get(0), AxisPitch.get(1), AxisPitch.get(2)));

		AxisYaw = Vec3MulMat3(AxisYaw, getRotationYZ(in_rotx));

		GlCall(int AxYaw_loc = glGetUniformLocation(program.get(), "modelAxisYaw"));
		GlCall(glUniform3f(AxYaw_loc, AxisYaw.get(0), AxisYaw.get(1), AxisYaw.get(2)));

		//std::cout << axRoll << AxisPitch << AxisYaw << std::endl;

		Mat3 Mrotz = { cos(rotz), -sin(rotz), 0,
					  sin(rotz), cos(rotz), 0,
					  0, 0, 1 };

		renderPos = Vec3MulMat3(renderPos, Mrotz);

		Vector3f pitchRot = { 1, 0, 0 };
		Vector3f yawRot = { 0, 1, 0 };

		pitchRot = Vec3MulMat3(pitchRot, Mrotz);
		yawRot = Vec3MulMat3(yawRot, Mrotz);

		renderPos = rotateVecAroundVecAx(renderPos, pitchRot, rotx);

		yawRot = rotateVecAroundVecAx(yawRot, pitchRot, rotx);

		renderPos = rotateVecAroundVecAx(renderPos, yawRot, roty);

		target.Draw(renderPos, program.get());*/
	}
}