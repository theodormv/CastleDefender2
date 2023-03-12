#include "Texture.h"

unsigned int Texture2D::unit_end = 0;

Texture2D::Texture2D(const char* fileName) {

	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0); // load the image
	
	unit = unit_end;
	++unit_end;

	GlCall(glGenTextures(1, &tex));
	Bind();


	if (data) {
		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		GlCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		ERROR("Failed to load texture");
	}

	
	stbi_image_free(data);

	//set the sampeling parameters

	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));



}

void Texture2D::Bind() const{
	//GlCall(glActiveTexture(GL_TEXTURE0 + unit));
	GlCall(glBindTexture(GL_TEXTURE_2D, tex));
}

void Texture2D::SetSampel(int samp_loc) const {
	return;

}