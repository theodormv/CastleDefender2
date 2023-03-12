#include "RollComponent.h"


namespace Components {
	Roll::Roll() : roll(0) {}
	Roll::Roll(float r) : roll(r) {}
	Roll::Roll(const Roll& other) : roll(other.roll) {}
}