#pragma once
#include "Component.h"

namespace Components {
	class Test : public Component {
	public:
		Test();

		void update() override;
	};
}

