#include "Model.h"


Model::Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size) : vb(vertices, vert_size), ib(indices, ind_size), tex(nullptr), axX(1,0,0), axY(0,1,0), axZ(0,0,1)
{
	vb.Bind();
	ib.Bind();
	vao.Bind();
	Primitive::TRIANGLE* tris = new Primitive::TRIANGLE[ind_size/3];

	Primitive::LoadTriangles(vb, ib, tris, ind_size / 3);

	Primitive::LoadVertexNormalsFromTriangles(tris, ind_size / 3, vb);

	vb.Update();


	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	//vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 2, GL_FLOAT, GL_FALSE });

	
	vb.SetVao(&vao);
}

Model::Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size, Vector3f x, Vector3f y, Vector3f z) : vb(vertices, vert_size), ib(indices, ind_size), tex(nullptr), axX(x), axY(y), axZ(z)
{

	vb.Bind();
	ib.Bind();
	vao.Bind();
	Primitive::TRIANGLE* tris = new Primitive::TRIANGLE[ind_size / 3];

	Primitive::LoadTriangles(vb, ib, tris, ind_size / 3);

	Primitive::LoadVertexNormalsFromTriangles(tris, ind_size / 3, vb);

	vb.Update();


	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	//vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 2, GL_FLOAT, GL_FALSE });


	vb.SetVao(&vao);
}


Model::Model(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size, baseTexture* tex) : vb(vertices, vert_size), ib(indices, ind_size), tex(tex), axX(1, 0, 0), axY(0, 1, 0), axZ(0, 0, 1)
{
	vb.Bind();
	ib.Bind();
	vao.Bind();
	Primitive::TRIANGLE* tris = new Primitive::TRIANGLE[ind_size / 3];

	Primitive::LoadTriangles(vb, ib, tris, ind_size / 3);

	Primitive::LoadVertexNormalsFromTriangles(tris, ind_size / 3, vb);

	vb.Update();

	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	//vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 2, GL_FLOAT, GL_FALSE });

	vb.SetVao(&vao);
}



void Model::Draw(const Point& pos, float rotx, float roty, float rotz, uint32 program) {
	int modelRot_loc = glGetUniformLocation(program, "modelRotation");
	GlCall(glUniform3f(modelRot_loc, rotx, roty, rotz));

	int modelPos_loc = glGetUniformLocation(program, "modelPosition");
	GlCall(glUniform3f(modelPos_loc, pos.x, pos.y, pos.z));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	if (tex) tex->Bind();
	GlCall(glDrawElements(GL_TRIANGLES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

void Model::Draw(const Vector3f& pos, float rotx, float roty, float rotz, uint32 program) {
	int modelRot_loc = glGetUniformLocation(program, "modelRotation");
	GlCall(glUniform3f(modelRot_loc, rotx, roty, rotz));

	int modelPos_loc = glGetUniformLocation(program, "modelPosition");
	GlCall(glUniform3f(modelPos_loc, pos.get(0), pos.get(1), pos.get(2)));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	if (tex) tex->Bind();
	GlCall(glDrawElements(GL_TRIANGLES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}


void Model::Draw(const Vector3f& pos, uint32 program) {


	int modelPos_loc = glGetUniformLocation(program, "modelPosition");
	GlCall(glUniform3f(modelPos_loc, pos.get(0), pos.get(1), pos.get(2)));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	if (tex) tex->Bind();
	GlCall(glDrawElements(GL_TRIANGLES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}