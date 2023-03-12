#pragma once
#include <GL/glew.h> // henter moderne gl fra drivere
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();

#define GlCall(x) clearGlErrors(); \
	x;\
	ASSERT(glGetCallError(#x, __FILE__, __LINE__))

#define ERROR(message) Error(message, __FILE__, __LINE__);


void clearGlErrors();

bool glGetCallError(const char* func, const char* file, int line);


void Error(const char* message);
void Error(const char* message, const char* file, int line);