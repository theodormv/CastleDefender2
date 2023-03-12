#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexAttributeArray.h"
#include "../VectorNd.h"
#include <algorithm>

typedef VectorNd<3, float> Vector3f;

namespace Primitive 
{
	typedef struct {
		unsigned int indices[3];
		Vector3f* VertexPositions[3];
		Vector3f Normal;
	} TRIANGLE;


	void LoadTriangles(const VertexBuffer& vbo, const IndexBuffer& vio, TRIANGLE* out_triangles, unsigned int triangle_num);

	void LoadVertexNormalsFromTriangles(const TRIANGLE* triangles, int triangleNum, VertexBuffer& vbo);


}