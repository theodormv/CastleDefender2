#include "VertexAttributeArray.h"


VertexAttributeArray::VertexAttributeArray() : m_end(0), m_stride(0) {
	GlCall(glGenVertexArrays(1, &m_vao));
	GlCall(glBindVertexArray(m_vao));
	std::cout << "CREATED VAO " << this << std::endl;
}

VertexAttributeArray::VertexAttributeArray(const VertexAttributeArray& other) : m_end(0), m_stride(other.m_stride), m_attributes(other.m_attributes) {
	GlCall(glGenVertexArrays(1, &m_vao));
	GlCall(glBindVertexArray(m_vao));
	std::cout << "COPIED VAO from " << &other << std::endl;


	PrintAttribs();

	SetGl();
}

VertexAttributeArray::~VertexAttributeArray() {
	GlCall(glDeleteVertexArrays(1, &m_vao));
}

void VertexAttributeArray::Bind() {
	GlCall(glBindVertexArray(m_vao));
}

void VertexAttributeArray::Push(VertexInputAttribute in_attribute) {
	VertexAttribute attribute;
	attribute = *(VertexAttribute*)&in_attribute;
	attribute.position = reinterpret_cast<void*>(m_stride);

	m_attributes.push_back(attribute);

	m_stride = calcPosition(m_attributes.size());
}

void VertexAttributeArray::PrintAttribs() {
	int i = 0;
	for (VertexAttribute& attribute : m_attributes) {
		std::cout << i++ << ", " << attribute.size << ", " << attribute.type << ", " << m_stride << ", " << attribute.position << std::endl;
	}
}

void VertexAttributeArray::SetGl() {
	GlCall(glBindVertexArray(m_vao));
	for (int i = 0; i < m_attributes.size(); i++) {
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(i, m_attributes[i].size, m_attributes[i].type, m_attributes[i].normalized, sizeof(Vertex), m_attributes[i].position));
		m_end++;
	}
	GlCall(glBindVertexArray(0));
}


unsigned int VertexAttributeArray::calcPosition(unsigned int index) {
	int position = 0;
	for (int i = 0; i < index; i++) {
		position += TranslateGlTypeSize(m_attributes[i].type) * m_attributes[i].size;
	}
	return position;
}



int TranslateGlTypeSize(GLenum type) {
	int size;
	switch (type)
	{
	case(GL_BYTE):
	case(GL_UNSIGNED_BYTE):
		size = sizeof(char);
		break;
	case(GL_FLOAT):
		size = sizeof(float);
		break;
	case(GL_DOUBLE):
		size = sizeof(double);
		break;
	case(GL_INT):
	case(GL_UNSIGNED_INT):
		size = sizeof(int);
		break;
	default:
		size = 0;
		break;
	}
	return size;
}