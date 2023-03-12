#pragma once
#include <string>
#include "../types.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace Shaders {
	const enum {
		Start = -1,
		Vertex,
		Fragment,
		End
	};
}



class ShaderSource {
public:


	std::stringstream sources[Shaders::End];

	ShaderSource();
	ShaderSource(const char* both);


	ShaderSource(const char* vertex, const char* fragment);

	void add(const char* file, int which_shader);




};