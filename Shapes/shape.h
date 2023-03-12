#pragma once
#include "../VectorNd.h"
#include <vector>
#include "../types.h"

class Sphere;
class BoxCore;
class GeneralPrism;


class Shape {

protected:
	std::vector<uint32>	inds;
	uint16 indCount;

	std::vector<Vector3f> points;

public:
	//virtual bool checkIntersect(Sphere* other) = 0;
	//virtual bool checkIntersect(GeneralPrism* other) = 0;
	virtual bool checkIntersect(BoxCore* other) = 0;

	//virtual Vector3f correctedIntersect(Sphere* other) = 0;
	//virtual Vector3f correctedIntersect(GeneralPrism* other) = 0;
	virtual Vector3f correctedIntersect(BoxCore* other) = 0;

	virtual bool checkPoint(const Vector3f& point) = 0;


	inline std::vector<Vector3f>& getPoints() { return points; }

	inline std::vector<uint32>& getInstructions() { return inds; }
};