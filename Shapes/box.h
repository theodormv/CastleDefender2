#pragma once
#include "boxcore.h"

class Box : public BoxCore {
public:
	Box() = default;
	Box(float w, float h, float d, Vector3f position);
	Box(const Box& other);
	~Box();
};