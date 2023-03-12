#include "TestComponent.h"
#include <iostream>

namespace Components {
	Test::Test() {}

	void Test::update() {
		std::cout << "This is a component of the entity " << owner << std::endl;
	}
}