#pragma once
#include "../VectorNd.h"
#include "Model.h"
#include "Wireframe.h"
#include "../Matrix3.h"
#include "Shader.h"
#include "cam.h"

class Camera : public Cam{
protected:
	Vector3f position;
	float rotx;
	float roty;
	float rotz;

	bool connected;

	
public:
	Camera();
	Camera(Vector3f pos);
	Camera(Vector3f pos, float rotx, float roty, float rotz);

	void Draw(Model& target, Vector3f position, float rotx, float roty, float rotz) override;

	void Draw(Model& target, Vector3f position, float rotx, float roty, float rotz, const Vector3f& axRoll, const Vector3f& axPitch, const Vector3f& axYaw) override;

	void Draw(Wireframe& target, Vector3f position, float rotx, float roty, float rotz) override;

	inline void rotatex(float rot) { rotx += rot; }
	inline void rotatey(float rot) { roty += rot; }
	inline void rotatez(float rot) { rotz += rot; }
	inline void move(Vector3f vec) { position += vec; }

	inline Vector3f getPos() { return position; }
	inline void setPos(Vector3f nPos) { position = nPos; }


};
