#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* indices, int size) : m_size(size), m_indices(indices) {
	GlCall(glGenBuffers(1, &m_vib));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vib));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(unsigned int), m_indices, GL_STATIC_DRAW));
	m_count = size / 3;
	internal_ind = false;
}

IndexBuffer::IndexBuffer(const IndexBuffer& other) : m_size(other.m_size), m_count(other.m_count) {
	m_indices = new unsigned int [m_size];
	for (int i = 0; i < m_size; ++i) {
		m_indices[i] = other.m_indices[i];
	}
	internal_ind =  true;

	GlCall(glGenBuffers(1, &m_vib));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vib));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(unsigned int), m_indices, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) : m_indices(other.m_indices), m_count(other.m_count), m_size(other.m_size), m_vib(other.m_vib), internal_ind(other.internal_ind) {
	other.m_indices = nullptr;
	other.m_vib = -1;
	other.internal_ind = false;

}

IndexBuffer::~IndexBuffer(){
	if(internal_ind)
		delete[] m_indices;
	
	
}

void IndexBuffer::Bind() {
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vib));
}
