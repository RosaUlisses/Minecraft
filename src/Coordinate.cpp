#include "Coordinate.h"

Coordinate::Coordinate(int x, int y, int z) {

	Coordinate::x = x;
	Coordinate::y = y;
	Coordinate::z = z;
}

bool Coordinate::operator==(const Coordinate& value) const {

	if (value.x == this->x && value.y == this->y && value.z == this->z) return true;
	return false;
}

