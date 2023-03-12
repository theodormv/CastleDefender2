#include "ModelComponent.h"
#include "../Entity.h"
#include "FacingComponent.h"
Cam* Components::Model::activeCam = nullptr;

namespace Components {
	Model::Model() : model(nullptr),worldPos(nullptr) {}

	Model::Model(::Model* mod) : model(mod) { worldPos = nullptr; }

	Model::Model(const Model& other) : worldPos(other.worldPos), model(other.model) {}

	Model::Model(Model&& other) noexcept : worldPos(other.worldPos), model(other.model) {
		other.model = nullptr;
		other.worldPos = nullptr;
	}

	void Model::update() {

		float xz = 0;
		float yz = 0;

		Vector3f rollAx = model->getAxZ();
		
		if (owner->hasComponent<Components::Facing>()) {
			Components::Facing* fac = owner->getComponent<Components::Facing>();

			xz = fac->getXZ();
			//std::cout << "ModelComponent : " << yaw << std::endl;
			yz = fac->getYZ();
		}
		
		activeCam->Draw(*model, worldPos->getPos(), yz, -xz, 0);
	}

	void Model::init() {
		worldPos = (Components::Position*)owner->getComponent<Components::Position>();
	}
}
