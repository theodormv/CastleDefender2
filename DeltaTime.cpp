#include "DeltaTime.h"
#include <iostream>
namespace Game {

	float dt;

	void updateDeltaTime() {
		static double lastTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000;

		double currentTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000;
		dt = currentTime - lastTime;
		lastTime = currentTime;
	}
}