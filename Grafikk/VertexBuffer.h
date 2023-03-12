#pragma once
#include "Error.h"
#include "VertexAttributeArray.h"
#include "../VectorNd.h"


class VertexBuffer {
	Vertex* m_vertices;
	int m_count;
	unsigned int m_vb;
	VertexAttributeArray* mp_vao;

public:
	VertexBuffer() = default;
	VertexBuffer(Vertex* vertecies, int size);
	VertexBuffer(const VertexBuffer& other);

	void Bind();
	void Update();
	inline unsigned int getReference()  const { return m_vb; }
	inline Vertex* getVertices() const { return m_vertices; }
	inline int getCount() const { return m_count; }
	void SetVao(VertexAttributeArray* vao);
};
