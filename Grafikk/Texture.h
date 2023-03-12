#pragma once
#include "Error.h"
#include "stb_image.h"
#include "baseTexture.h"


class Texture2D : public baseTexture{
	int width;
	int height;
	int nrChannels;
	unsigned int tex;
	unsigned int unit;
	static unsigned int unit_end;

public:
	Texture2D() = default;
	Texture2D(const char* fileName);
	
	void Bind() const override;
	void SetSampel(int samp_loc) const;
};