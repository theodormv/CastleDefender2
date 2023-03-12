#include "PositionComponent.h"


namespace Components {
	Position::Position() : pos(0, 0, 0) {}
	Position::Position(float x, float y, float z) : pos(x,y,z) {}
	Position::Position(Vector3f vec) : pos(vec) {}
	Position::Position(const Position& other) : pos(other.pos) {}
	Position::Position(Position&& other) : pos(other.pos) {}


}