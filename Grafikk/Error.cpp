#include "Error.h"

void clearGlErrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool glGetCallError(const char* func, const char* file, int line) {
	GLenum err;
	bool error = true;
	while ((err = glGetError()) != GL_NO_ERROR) {

		std::cout << "[gl error] (" << err << "): " << file << " " << line << std::endl;

		error = false;
	}
	return error;
}


void Error(const char* message) {
	std::cout << "[ERROR] : " << message << std::endl;
	exit(0);
}

void Error(const char* message, const char* file, int line) {
	std::cout << "[ERROR] : " << message << ": in " << file << " at " << line << std::endl;
	__debugbreak();
}