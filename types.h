#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"



#define UINT unsigned int

typedef short UINT uint16;
typedef UINT uint32;
typedef long UINT uint64;
typedef unsigned char byte;

typedef short int16;
typedef int int32;
typedef long int64;


typedef struct {
	GLFWwindow* context;
	uint16 width;
	uint16 height;
	const char* name;
} Window;

typedef struct {
	float x;
	float y;
	float z;
} Point;