#pragma once

#include "../Component.h"
#include "PositionComponent.h"

#include "../Grafikk/Camera.h"
#include "../Grafikk/Texture.h"
#include "../Grafikk/Model.h"

namespace Components {
	class Model : public Component {
		Position* worldPos;
		::Model* model;
	public:
		Model();
		Model(::Model* mod);
		Model(const Model& other);
		Model(Model&& other) noexcept;


		void update() override;
		void init() override;

		inline void setModel(::Model* mod) { model = mod; }

		inline ::Model* getModel() { return model; }

		static Cam* activeCam;
	};
}