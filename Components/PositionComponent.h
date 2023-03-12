#pragma once
#include "../VectorNd.h"
#include "../Component.h"
#include <iostream>
namespace Components {
	class Position : public Component {
		Vector3f pos;
	public:

		Position();
		Position(float x, float y, float z);
		Position(Vector3f vec);
		Position(const Position& other);
		Position(Position&& other);


		inline Vector3f& getPos() { return pos; }

		inline void update() override {}
	};
}