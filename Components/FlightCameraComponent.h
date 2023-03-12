#pragma once
#include "../Component.h"
#include "../Grafikk/Camera.h"
#include "PositionComponent.h"
#include "FacingComponent.h"
#include "RollComponent.h"


namespace Components {
	class FlightCamera : public Component, public Cam {

		Position* pos;
		Roll* roll;
		Facing* fac;

	public:

		FlightCamera();
		void init() override;
		void update() override;

		void Draw(::Model& target, Vector3f pos, float roll, float pitch, float yaw) override;

		void Draw(::Model& target, Vector3f position, float rotx, float roty, float rotz, const Vector3f& axRoll, const Vector3f& axPitch, const Vector3f& axYaw) override;

	};
}
