#pragma once
#include "Shader.h"


Shader::Shader() { 
	GlCall(glProgram = glCreateProgram());
}

Shader::Shader(const ShaderSource& source) {
	GlCall(glProgram = glCreateProgram());
	Create(source);
}

uint32 Shader::Compile(uint32 type, const char* source ) {
	uint32 shader = glCreateShader(type);
	GlCall(glShaderSource(shader, 1, &source, nullptr));
	GlCall(glCompileShader(shader));

	int32 success = 0;
	GlCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		int32 logsize = 0;
		GlCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize));

		char* error = (char*) malloc(logsize);
	
		GlCall(glGetShaderInfoLog(shader, logsize, 0, error));

		Error(error);

		GlCall(glDeleteShader(shader));
		return 0;
	}

	return shader;
}


unsigned int Shader::Create(const ShaderSource& source) {


	uint32 vertex = Compile(GL_VERTEX_SHADER, source.sources[Shaders::Vertex].str().c_str());
	uint32 fragment = Compile(GL_FRAGMENT_SHADER, source.sources[Shaders::Fragment].str().c_str());

	GlCall(glAttachShader(glProgram, vertex));
	GlCall(glAttachShader(glProgram, fragment));

	GlCall(glLinkProgram(glProgram));

	int32 success = 0;
	GlCall(glGetProgramiv(glProgram, GL_LINK_STATUS, &success));
	if (success == GL_FALSE) {
		int32 logsize = 0;
		GlCall(glGetProgramiv(glProgram, GL_INFO_LOG_LENGTH, &logsize));

		char* error = (char*)malloc(logsize);

		GlCall(glGetProgramInfoLog(glProgram, logsize, 0, error));

		Error(error);

		GlCall(glDeleteProgram(glProgram));
		return 0;
	}

	GlCall(glDetachShader(glProgram, vertex));
	GlCall(glDetachShader(glProgram, fragment));

	return glProgram;

}


void Shader::Use() const {
	GlCall(glUseProgram(glProgram));
}

uint32 Shader::get() const { return glProgram; }