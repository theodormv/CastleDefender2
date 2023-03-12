#pragma once
#include "../Component.h"
#include "../Grafikk/Camera.h"

namespace Components {
	class Camera : public Component, public ::Camera {
		
	public:
		Camera();
	
		void update() override;

		void init() override;

	
	
	};
}