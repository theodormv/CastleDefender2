#pragma once
#include "Error.h"
#include <vector>

typedef struct {
	float position[3]; //position MUST ALWAYS be the first member
	//float color[3];
	float normal[3];
	float textureCorrd[2];
} Vertex;

 
typedef struct {
	int size; // number of elements in the attribute
	GLenum type; // datatype of the elements
	GLboolean normalized; // should values be normalized	
} VertexInputAttribute;

typedef struct {
	int size; // number of elements in the attribute
	GLenum type; // datatype of the elements
	GLboolean normalized; // should values be normalized	
	void* position;
} VertexAttribute;



class VertexAttributeArray {
	unsigned int m_vao;
	unsigned int m_end;
	unsigned int m_stride;
	std::vector<VertexAttribute> m_attributes;
	friend class VertexBuffer;
public:
	VertexAttributeArray();
	VertexAttributeArray(const VertexAttributeArray& other);
	~VertexAttributeArray();
	void Bind();
	//void Enable(unsigned int slot);
	//void Disable(unsigned int slot);
	//void Set(unsigned int slot, VertexInputAttribute attribute);
	void Push(VertexInputAttribute attribute);
	//void Pop();
	inline unsigned int getStride() {
		return m_stride;
	}
	
	void PrintAttribs();
private:
	unsigned int calcPosition(unsigned int index);
	void SetGl();
};

int TranslateGlTypeSize(GLenum type);