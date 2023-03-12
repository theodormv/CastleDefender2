#pragma once
#include "VertexAttributeArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Triangles.h"
#include "Texture.h"
#include "TextureCube.h"
#include "../types.h"


class Model {
	VertexBuffer vb;
	IndexBuffer ib;
	VertexAttributeArray vao;
	
	baseTexture* tex;

	Vector3f axX;
	Vector3f axY;
	Vector3f axZ;

public:
	Model() = default;
	Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size);							   
	Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size, Vector3f x, Vector3f y, Vector3f z);

	Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size, baseTexture* tex);

	void Draw(const Point& pos, float rotx, float roty, float rotz, uint32 program);

	void Draw(const Vector3f& pos, float rotx, float roty, float rotz, uint32 program);

	void Draw(const Vector3f& pos, uint32 program);

	inline Vector3f getAxX () {return axX; }
	inline Vector3f getAxY () {return axY; }
	inline Vector3f getAxZ () {return axZ; }
};