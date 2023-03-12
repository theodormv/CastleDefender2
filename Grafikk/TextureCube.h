#pragma once
#include "Error.h"
#include "stb_image.h"
#include "baseTexture.h"


class TextureCube : public baseTexture {
	int width, height;
	int nrChannels;
	unsigned int tex;
	unsigned int unit;
	static unsigned int unit_end;

public:
	TextureCube() = default;
	TextureCube(const char* fileName);

	void Bind() const override;
	void SetSampel(int samp_loc) const;
};