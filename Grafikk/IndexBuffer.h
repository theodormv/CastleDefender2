#pragma once
#include "Error.h"

class IndexBuffer {
	unsigned int* m_indices;
	int m_count; //number of triangles
	int m_size;
	unsigned int m_vib;


	bool internal_ind;
public:
	IndexBuffer() = default;
	IndexBuffer(unsigned int* indices, int size);
	IndexBuffer(const IndexBuffer& other);
	IndexBuffer(IndexBuffer&& other);
	~IndexBuffer();

	void Bind();
	inline unsigned int getGlReference() const { return m_vib; }
	inline unsigned int getCount() const { return m_count; }
	inline unsigned int getSize() const { return m_size; }
	inline unsigned int* getIndices() const { return m_indices; }
};