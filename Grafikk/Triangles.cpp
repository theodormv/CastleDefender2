#include "Triangles.h"


void Primitive::LoadTriangles(const VertexBuffer& vbo, const IndexBuffer& vio, Primitive::TRIANGLE* out_triangles, unsigned int num) {
	const int vertCount = vbo.getCount();
	const Vertex* vertData = vbo.getVertices();
	const unsigned int* indices = vio.getIndices();

	for (int i_tri = 0; i_tri < num; i_tri++) {
		TRIANGLE& this_tri = out_triangles[i_tri];
		for (int vertNum = 0; vertNum < 3; vertNum++) {
			//load index
			this_tri.indices[vertNum] = indices[3 * i_tri + vertNum];
			if (this_tri.indices[vertNum] >= vertCount)
				ERROR("Index out of range");

			//load pointer to position specified by previous index
			this_tri.VertexPositions[vertNum] = (Vector3f*)&vertData[this_tri.indices[vertNum]].position; // OK because Vector3f only stores 3 floats
		}

		Vector3f first =  *this_tri.VertexPositions[0] - *this_tri.VertexPositions[1];
		Vector3f second = *this_tri.VertexPositions[2] - *this_tri.VertexPositions[1];

		this_tri.Normal = cross(second, first);
		this_tri.Normal.norm();
		//std::cout << this_tri.Normal << std::endl;
	}
	
}

void Primitive::LoadVertexNormalsFromTriangles(const Primitive::TRIANGLE* triangles, int triangleNum, VertexBuffer& vbo) {
	Vertex* vertices = vbo.getVertices();
	int vertexCount = vbo.getCount();
	std::vector<std::vector<Vector3f>> planes;
	planes.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		planes.push_back(std::vector<Vector3f>());
	}

	for (int i_tri = 0; i_tri < triangleNum; i_tri++) {
		for (int i_ind = 0; i_ind < 3; i_ind++) {
			if (triangles[i_tri].indices[i_ind] >= vertexCount)
				ERROR("Index out of range");
			
			int index = triangles[i_tri].indices[i_ind];

			if (std::find(planes[index].begin(), planes[index].end(), triangles[i_tri].Normal) == planes[index].end()) {
				planes[index].push_back(triangles[i_tri].Normal);
			}
			
			
		}
	}

	for (int i_vert = 0; i_vert < vertexCount; i_vert++) {
		Vector3f NormalSum;
		for (int i_norm = 0; i_norm < planes[i_vert].size(); i_norm++) {
			NormalSum += planes[i_vert][i_norm];
		}
		*(Vector3f*)&vertices[i_vert].normal = NormalSum/NormalSum.mag();
	}
}