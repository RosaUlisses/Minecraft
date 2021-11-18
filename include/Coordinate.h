#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {

	public:

		int x;
		int y;
		int z;

		Coordinate(int x, int y, int z);

		bool operator==(const Coordinate& value) const;

		struct HahsFunction {

			size_t operator()(const Coordinate& value) const {

				size_t hash_x_y = 5 * (value.x + value.y) * (value.x, value.y) + value.y;
				size_t hash_code = 5 * (hash_x_y + value.z) * (hash_x_y + value.z + 1) + value.z;
				return hash_code;
			}
		};
};

#endif