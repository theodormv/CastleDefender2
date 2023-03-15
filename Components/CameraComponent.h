#pragma once
#include "../Component.h"
#include "../Grafikk/nyttCamera.h"

namespace Components {
	class Camera : public Component, public ::newCamera {
		
	public:
		Camera();
	
		void update() override;

		void init() override;

	
	
	};
}