#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(Vertex* vertices, int size) : m_count(size), m_vertices(vertices) {

	/*
	float maxLen = reinterpret_cast<Vector3f*>(vertices)->sqareMag();

	for (int i = 1; i < size; ++i) {
		if (maxLen < reinterpret_cast<Vector3f*>(&vertices[i])->sqareMag()) {
			maxLen = reinterpret_cast<Vector3f*>(&vertices[i])->sqareMag();
		}
	}

	for(int i = 0; i < size; ++i){
	
		*reinterpret_cast<Vector3f*>(&vertices[i]) /= maxLen;

	}
	*/



	GlCall(glGenBuffers(1, &m_vb));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
	GlCall(glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Vertex), (float*)m_vertices, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const VertexBuffer& other) : m_count(other.m_count) {

	m_vertices = new Vertex[m_count];
	for (int i = 0; i < m_count; ++i) {

		m_vertices[i] = other.m_vertices[i];

	}


	GlCall(glGenBuffers(1, &m_vb));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
	GlCall(glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Vertex), (float*)m_vertices, GL_STATIC_DRAW));

	mp_vao = new VertexAttributeArray(*other.mp_vao);

}


void VertexBuffer::Bind() {
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
}

void VertexBuffer::Update() {
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
	GlCall(glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Vertex), m_vertices, GL_STATIC_DRAW));
}

void VertexBuffer::SetVao(VertexAttributeArray* vao) {
	mp_vao = vao;
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
	mp_vao->SetGl();
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}