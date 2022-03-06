#include "Coordinate.h"

Coordinate::Coordinate()
{
	x = 0;
	y = 0;
	z = 0;
}

Coordinate::Coordinate(int x, int y, int z) {

	this->x = x;
	this->y = y;
	this->z = z;
}

bool Coordinate::operator==(const Coordinate& value) const {

	if (value.x == this->x && value.y == this->y && value.z == this->z) return true;
	return false;
}

double Coordinate::Distance(Coordinate coordinate){
	return sqrt(pow(x - coordinate.x, 2) + pow(y - coordinate.y, 2) + pow(z - coordinate.z, 2));
}

Coordinate Coordinate::operator+(const Coordinate& value) const{
	return { value.x + x, value.y + y, value.z + z };
}





