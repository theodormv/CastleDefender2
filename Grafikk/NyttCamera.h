#pragma once
#include "cam.h"
#include "glm/mat4x4.hpp" //hentet fra https://github.com/g-truc/glm/tree/master/glm
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class newCamera : public Cam {

protected:
	Vector3f Direction;
	Vector3f* position;
	Vector3f up;

	float viewMatix[4][4];

public:

	newCamera();
	newCamera(Vector3f position, Vector3f targetPos);

	void Draw(Model& target, Vector3f pos, float rotx, float roty, float rotz) override;
	

	void setViewMatrix();


private:
	void initVecs();
};


glm::vec3 convMyVec(const Vector3f& myvec);