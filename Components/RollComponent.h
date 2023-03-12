#pragma once
#include "../Component.h"

namespace Components {

	class Roll : public Component {
		float roll;

	public:
		Roll();
		Roll(float Roll);
		Roll(const Roll& other);


		inline float getRoll() { return roll; }
		inline void rotateRoll(float rad) { roll += rad; }

		void update() override {
			//roll += 0.001f;
		}


	};


}