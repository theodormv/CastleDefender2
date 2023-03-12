#pragma once
#include "../VectorNd.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../types.h"
#include <iostream>

enum {
	XBOX_LEFT_X_AXIS,
	XBOX_LEFT_Y_AXIS,
	XBOX_RIGHT_X_AXIS,
	XBOX_RIGHT_Y_AXIS,
	XBOX_LEFT_TRIGGER,
	XBOX_RIGHT_TRIGGER,
};


namespace Input {
	class Controller {

		int32 number;
		int32 axCount;
		int32 btCount;

		float* axStates;
		byte* btStates;


	public:

		Controller() = default;
		Controller(uint32 num);

		~Controller();


		void update();

		inline float getAx(uint16 s) { return axStates[s]; }
		inline float* getAxp(uint16 s) { return &axStates[s]; }

		inline byte getBt(uint16 s) { return btStates[s]; }
		inline byte* getBtp(uint16 s) { return &btStates[s]; } 	

		inline bool present() { return  glfwJoystickPresent(number); }

	};



}