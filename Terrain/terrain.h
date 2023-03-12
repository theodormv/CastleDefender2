#pragma once

#include "../Shapes/shape.h"
#include "../Shapes/box.h"
#include "../Grafikk/Model.h"
#include <vector>

class Terrain {
	Shape* shape;
	Model* model;

public:

	Terrain() = default;
	Terrain(float w, float h, float d, Vector3f pos);
	Terrain(const Terrain& other);

	~Terrain();
	
	void draw() const;

	inline Shape* getShape() const { return shape; }

	static TextureCube* tex;
};