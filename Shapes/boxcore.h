#pragma once
#include "shape.h"

class BoxCore : public Shape {

protected:
	float width;
	float height;
	float depth;
	Vector3f* center;

public:

	BoxCore() = default;
	BoxCore(float w, float h, float d);
	BoxCore(const BoxCore& other);

	bool checkIntersect(BoxCore* other) override;
	Vector3f correctedIntersect(BoxCore* other) override;
	
	bool checkPoint(const Vector3f& points) override;

	inline Vector3f getCenter() { return *center; }

	inline float getWidth () const { return width; }
	inline float getHeight () const { return height; }
	inline float getDepth () const { return depth; }

	inline Vector3f getFurthestPoint() const { return Vector3f(abs(width / 2), abs(height / 2), abs(depth / 2)); }
};

