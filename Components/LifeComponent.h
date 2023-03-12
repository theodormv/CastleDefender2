#pragma once

#include "../Component.h"
#include "../types.h"

namespace Components {
	class Life : public Component {

		int32 life;
	
	public:

		Life() = default;
		Life(int32 l);

		void update() override;
		void init() override;

		inline int32& getLife() { return life; }
	};
}