#include "Camera.h"


Camera::Camera() : position(0, 0, 0), rotx(0), roty(0), rotz(0) {}
Camera::Camera(Vector3f pos) : position(pos), rotx(0), roty(0), rotz(0) {}
Camera::Camera(Vector3f pos, float rotx, float roty, float rotz) : position(pos), rotx(rotx), roty(roty), rotz(rotz) {}


void Camera::Draw(Model& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz) {
	Vector3f renderPos = in_position - position;
	//std::cout << renderPos << std::endl;

	program.Use();

	GlCall(int camRot_loc = glGetUniformLocation(program.get(), "cameraRotation"));
	GlCall(glUniform3f(camRot_loc, rotx, roty, rotz));


	GlCall(int posRot_loc = glGetUniformLocation(program.get(), "positionRotation"));
	GlCall(glUniform3f(posRot_loc, rotx, roty, rotz));



	GlCall(int axPitch_loc = glGetUniformLocation(program.get(), "modelAxisPitch"));

	Vector3f pitchAx(1, 0, 0);
	pitchAx = Vec3MulMat3(pitchAx, getRotationXZ(roty));
	std::cout << "Camera::draw" << pitchAx << rotx << " " << roty << std::endl;

	GlCall(glUniform3f(axPitch_loc, pitchAx[0], pitchAx[1], pitchAx[2]));



	target.Draw(renderPos, in_rotx, in_roty, in_rotz, program.get());
}


/*void Camera::Draw(Model& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz, const Vector3f& axRoll, const Vector3f& axPitch, const Vector3f& axYaw) {
	Vector3f renderPos = in_position - position;
	//std::cout << renderPos << std::endl;

	program.Use();


	GlCall(int modRot_loc = glGetUniformLocation(program.get(), "modelRotation"));
	GlCall(glUniform3f(modRot_loc, in_rotx, in_roty, in_rotz));

	std::cout << "Camera::draw with axes : " << (in_rotx/PI * 180.f) << " " << (in_roty/PI * 180.f) << std::endl;


	GlCall(int camRot_loc = glGetUniformLocation(program.get(), "cameraRotation"));
	GlCall(glUniform3f(camRot_loc, rotx, roty, rotz));


	//std::cout << Vector3f(sin(roty) * cos(rotx), sin(roty) * cos(rotx), cos(roty)) << axRoll << std::endl;


	Vector3f AxisRoll = axRoll;



	
	GlCall(int AxRoll_loc = glGetUniformLocation(program.get(), "modelAxisRoll"));
	GlCall(glUniform3f(AxRoll_loc, AxisRoll.get(0), AxisRoll.get(1), AxisRoll.get(2)));

	/*
	GlCall(int AxPitch_loc = glGetUniformLocation(program.get(), "modelAxisPitch"));
	GlCall(glUniform3f(AxPitch_loc, AxisPitch.get(0), AxisPitch.get(1), AxisPitch.get(2)));

	GlCall(int AxYaw_loc = glGetUniformLocation(program.get(), "modelAxisYaw"));
	GlCall(glUniform3f(AxYaw_loc, AxisYaw.get(0), AxisYaw.get(1), AxisYaw.get(2)));

	
	//std::cout << axRoll << AxisPitch << AxisYaw << std::endl;

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

	target.Draw(renderPos, program.get());
}

void Camera::Draw(Wireframe& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz) {
	Vector3f renderPos = in_position - position;
	//std::cout << renderPos << std::endl;

	program.Use();


	GlCall(int modRot_loc = glGetUniformLocation(program.get(), "modelRotation"));
	GlCall(glUniform3f(modRot_loc, in_rotx, in_roty, in_rotz));

	std::cout << "Camera::draw with axes : " << (in_rotx / PI * 180.f) << " " << (in_roty / PI * 180.f) << std::endl;


	GlCall(int camRot_loc = glGetUniformLocation(program.get(), "cameraRotation"));
	GlCall(glUniform3f(camRot_loc, rotx, roty, rotz));


	//std::cout << Vector3f(sin(roty) * cos(rotx), sin(roty) * cos(rotx), cos(roty)) << axRoll << std::endl;



	/*
	GlCall(int AxPitch_loc = glGetUniformLocation(program.get(), "modelAxisPitch"));
	GlCall(glUniform3f(AxPitch_loc, AxisPitch.get(0), AxisPitch.get(1), AxisPitch.get(2)));

	GlCall(int AxYaw_loc = glGetUniformLocation(program.get(), "modelAxisYaw"));
	GlCall(glUniform3f(AxYaw_loc, AxisYaw.get(0), AxisYaw.get(1), AxisYaw.get(2)));

	
	//std::cout << axRoll << AxisPitch << AxisYaw << std::endl;

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

	target.Draw(renderPos, program.get());
}*/