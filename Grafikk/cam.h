#pragma once
#include "Model.h"
#include "Wireframe.h"
#include "Shader.h"
#include "../VectorNd.h"

class Cam {
public:
	virtual void Draw(Model& target, Vector3f pos, float rotx, float roty, float rotz) = 0;
	
	virtual void Draw(Model& target, Vector3f position, float rotx, float roty, float rotz, const Vector3f& axRoll, const Vector3f& axPitch, const Vector3f& axYaw) = 0;
	virtual void Draw(Wireframe& target, Vector3f position, float rotx, float roty, float rotz) = 0;

	Shader program;
};