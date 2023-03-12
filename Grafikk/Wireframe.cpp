#include "Wireframe.h"


Wireframe::Wireframe(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size) : vb(vertices, vert_size), ib(indices, ind_size), axX(1, 0, 0), axY(0, 1, 0), axZ(0, 0, 1)
{
	vb.Bind();
	ib.Bind();
	vao.Bind();

	vb.Update();

	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	//vao.Push({ 2, GL_FLOAT, GL_FALSE });

	vb.SetVao(&vao);
}

Wireframe::Wireframe(Vertex* vertices, int vert_size, unsigned int* indices, int ind_size, Vector3f x, Vector3f y, Vector3f z) : vb(vertices, vert_size), ib(indices, ind_size), axX(x), axY(y), axZ(z)
{

	vb.Bind();
	ib.Bind();
	vao.Bind();

	vb.Update();

	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	vao.Push({ 3, GL_FLOAT, GL_FALSE });
	//vao.Push({ 2, GL_FLOAT, GL_FALSE });

	vb.SetVao(&vao);
}




void Wireframe::Draw(const Point& pos, float rotx, float roty, float rotz, uint32 program) {
	int WireframeRot_loc = glGetUniformLocation(program, "ModelRotation");
	GlCall(glUniform3f(WireframeRot_loc, rotx, roty, rotz));

	int WireframePos_loc = glGetUniformLocation(program, "ModelPosition");
	GlCall(glUniform3f(WireframePos_loc, pos.x, pos.y, pos.z));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	GlCall(glDrawElements(GL_LINES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

void Wireframe::Draw(const Vector3f& pos, float rotx, float roty, float rotz, uint32 program) {
	int WireframeRot_loc = glGetUniformLocation(program, "ModelRotation");
	GlCall(glUniform3f(WireframeRot_loc, rotx, roty, rotz));

	int WireframePos_loc = glGetUniformLocation(program, "ModelPosition");
	GlCall(glUniform3f(WireframePos_loc, pos.get(0), pos.get(1), pos.get(2)));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	GlCall(glDrawElements(GL_LINES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}


void Wireframe::Draw(const Vector3f& pos, uint32 program) {


	int WireframePos_loc = glGetUniformLocation(program, "ModelPosition");
	GlCall(glUniform3f(WireframePos_loc, pos.get(0), pos.get(1), pos.get(2)));

	vb.Bind();
	ib.Bind();
	vao.Bind();
	GlCall(glDrawElements(GL_LINES, ib.getSize(), GL_UNSIGNED_INT, nullptr));

	GlCall(glBindVertexArray(0));
	GlCall(glUseProgram(0));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}