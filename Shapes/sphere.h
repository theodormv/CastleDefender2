#pragma once
#include "shape.h"
#include "../VectorNd.h"

class Sphere : public Shape {
	float r;
	Vector3f sentrum;
public:
	Sphere() = default;
	Sphere(float r, Vector3f sentrum);
	
	//bool checkIntersect(Sphere* other) override;
	bool checkIntersect(GeneralPrism* other) override;



};