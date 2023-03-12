#pragma once
#include "../Component.h"

#pragma once

#include "../Component.h"
#include "PositionComponent.h"

#include "../Grafikk/Camera.h"
#include "../Grafikk/Wireframe.h"

namespace Components {
	class Wireframe : public Component {
		Position* worldPos;
		::Wireframe* wireframe;
	public:
		Wireframe();
		Wireframe(::Wireframe* mod);
		Wireframe(const Wireframe& other);
		Wireframe(Wireframe&& other) noexcept;


		void update() override;
		void init() override;

		inline void setModel(::Wireframe* mod) { wireframe = mod; }

		inline ::Wireframe* getModel() { return wireframe; }

		static Cam* activeCam;
	};
}