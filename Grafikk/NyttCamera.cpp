#include "NyttCamera.h"

newCamera::newCamera() : Direction(0, 0, 1), position(new Vector3f(0, 0, 0)), up(0,1,0) {
	initVecs();
}

newCamera::newCamera(Vector3f position, Vector3f targetPos) : position(new Vector3f(position)), Direction(targetPos - position), up(0, 1, 0) {
	initVecs();
}

void newCamera::initVecs() {}

void newCamera::Draw(Model& target, Vector3f in_position, float in_rotx, float in_roty, float in_rotz) {
	//Vector3f renderPos = in_position - *position;
	//std::cout << renderPos << std::endl;

	program.Use();

	setViewMatrix();
	
	//std::cout << "Tegner" << std::endl;
	target.Draw(in_position, in_rotx, in_roty, in_rotz, program.get());
}


void newCamera::setViewMatrix() {

	program.Use();
	
	glm::mat4 lookAtMatrix;

	lookAtMatrix = glm::lookAt(convMyVec(*position), convMyVec(*position + Direction), convMyVec(up));



	GlCall(int mat_loc = glGetUniformLocation(program.get(), "lookAtMat"));
	GlCall(glUniformMatrix4fv(mat_loc, 1, GL_FALSE, &lookAtMatrix[0][0]));


}

glm::vec3 convMyVec(const Vector3f& myvec) {

	glm::vec3 retVec = { myvec.get(0), myvec.get(1), myvec.get(2) };
	return retVec;
}