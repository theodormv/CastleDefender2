#include "TextureCube.h"

unsigned int TextureCube::unit_end = 0;

TextureCube::TextureCube(const char* fileName) {


	unit = unit_end;
	++unit_end;

	GlCall(glGenTextures(1, &tex));
	Bind();


	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	stbi_image_free(data);

	//set the sampeling parameters

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);


}

void TextureCube::Bind() const {
	//GlCall(glActiveTexture(GL_TEXTURE0 + unit));
	GlCall(glBindTexture(GL_TEXTURE_CUBE_MAP, tex));
}

void TextureCube::SetSampel(int samp_loc) const {
	return;

}