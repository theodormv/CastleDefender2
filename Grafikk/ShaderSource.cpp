#include "ShaderSource.h"


ShaderSource::ShaderSource() {
}



ShaderSource::ShaderSource(const char* both) {


	std::ifstream infile(both);

	int working = Shaders::Start;
	std::stringstream* workingSource = &sources[Shaders::Vertex];

	std::string line;

	while (std::getline(infile, line)) {

		if (line.find("#shader") != std::string::npos) {
			workingSource = &sources[++working];
			continue;
		}
			
			

		*workingSource << line << '\n';

	}

	infile.close();

}



ShaderSource::ShaderSource(const char* vertex, const char* fragment){

	std::ifstream infile(vertex);
	std::string line;


	while (std::getline(infile, line)) {
		sources[Shaders::Vertex] << line;
	}

	infile.close();


	infile.open(fragment);
	while (std::getline(infile, line)) {
		sources[Shaders::Fragment] << line;
	}
	infile.close();

}

void ShaderSource::add(const char* file, int which_shader){

	std::ifstream infile(file);
	std::string line;

	while (std::getline(infile, line)) {
		sources[which_shader] << line;
	}

	infile.close();
}