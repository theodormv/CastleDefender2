#include "Controller.h"


namespace Input {

	Controller::Controller(uint32 num) : number(num) {
		uint32 present = glfwJoystickPresent(number);

		const float* axes = glfwGetJoystickAxes(number, &axCount);
		const byte* bts = glfwGetJoystickButtons(number, &btCount);

		axStates = new float[axCount];
		btStates = new byte[btCount];

		std::cout << "Joystick " << number << " status: " << present << std::endl;
	}

	Controller::~Controller(){
		delete[] axStates;
		delete[] btStates;
	}


	void Controller::update() {
		uint32 present = glfwJoystickPresent(number);

		

		if (present != GLFW_TRUE) {
			for (int i = 0; i < axCount; ++i) {
				axStates[i] = 0;
 				//	std::cout << states[i] << std::endl;
			}
			for (int i = 0; i < btCount; ++i) {
				btStates[i] = 0;
			}
			return;
		}

		const float* axes = glfwGetJoystickAxes(number, &axCount);

		for (int i = 0; i < axCount; ++i) {
			axStates[i] = axes[i];
		//	std::cout << states[i] << std::endl;
		}

		const byte* bts = glfwGetJoystickButtons(number, &btCount);

		for (int i = 0; i < btCount; ++i) {
			btStates[i] = bts[i];
			//std::cout << (int)btStates[i] << std::endl;
		}

		//printf("\n\n\n\n\n\n");

	}


}
