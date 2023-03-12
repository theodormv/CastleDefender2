#pragma once
#include <string>
#include "Error.h"
#include "../types.h"
#include "ShaderSource.h"



class Shader {
	uint32 glProgram;

public:
	
	Shader();
	Shader(const ShaderSource& source);

	uint32 Create(const ShaderSource& source); // called after the source has been completed 

	void Use() const;

	uint32 get() const;

	
private:
	uint32 Compile(uint32 type, const char* source); // compiles each shader type into the apropriate 

};
