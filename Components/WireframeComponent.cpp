#include "WireframeComponent.h"
#include "../Entity.h"
#include "FacingComponent.h"
Cam* Components::Wireframe::activeCam = nullptr;

namespace Components {
	Wireframe::Wireframe() : wireframe(nullptr), worldPos(nullptr) {}

	Wireframe::Wireframe(::Wireframe* mod) : wireframe(mod) { worldPos = nullptr; }

	Wireframe::Wireframe(const Wireframe& other) : worldPos(other.worldPos), wireframe(other.wireframe){}

	Wireframe::Wireframe(Wireframe&& other) noexcept : worldPos(other.worldPos), wireframe(other.wireframe) {
		other.wireframe = nullptr;
		other.worldPos = nullptr;
	}

	void Wireframe::update() {

		float xz = 0;
		float yz = 0;
		float roll = 0;

		Vector3f rollAx = wireframe->getAxZ();

		if (owner->hasComponent<Components::Facing>()) {
			Components::Facing* fac = owner->getComponent<Components::Facing>();

			xz = fac->getXZ();
			//std::cout << "WireframeComponent : " << yaw << std::endl;
			yz = fac->getYZ();

		}

		//activeCam->Draw(*wireframe, worldPos->getPos(), yz, xz, 0);
	}

	void Wireframe::init() {
		worldPos = (Components::Position*)owner->getComponent<Components::Position>();
	}
}
