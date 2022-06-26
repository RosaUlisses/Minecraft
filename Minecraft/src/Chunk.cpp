
#include "Chunk.hpp"



double Remap(double value, double oldMin, double oldMax, double newMin, double newMax) {
	return (value - oldMin) / (oldMax - oldMin) * (newMax - newMin) + newMin;
}

Block Blocks[] = {
	Block("coblestone", 0),
	Block("grass", 3, 1, 2),
	Block("stone", 4),
	Block("dirt", 1)
};

bool Chunk::is_there_a_block(Coordinate coord) {

	int i = coord.x - coordinate.x;
	int j = coord.y - coordinate.y;
	int k = coord.z - coordinate.z;

	

	if (i < 0 || i >= X_DIMENSION) return false;

	if (j < 0 || j >= Y_DIMENSION) return false;

	if (k < 0 || k >= Z_DIMENSION) return false;

	if (matrix[i][j][k] == EMPTY_BLOCK) return false;

	return true;
}


Chunk::Chunk(Coordinate coordinate, FastNoiseLite continentalnessNoise, FastNoiseLite erosionNoise, FastNoiseLite warp_erosionNoise) {

	this->coordinate = coordinate;

	for (int x = 0; x < X_DIMENSION; x++) {
		for (int y = 16; y < Y_DIMENSION; y++){
			for (int z = 0; z < Z_DIMENSION; z++) {
				matrix[x][y][z] = -1;
			}
		}
	}

	for (int x = 0; x < X_DIMENSION; x++) {
		for (int z = 0; z < Z_DIMENSION; z++) {

			double noise = continentalnessNoise.GetNoise((float)(coordinate.x + x), (float)(coordinate.z + z));
			float warpX = (coordinate.x + x), warpZ = (coordinate.z + z);
			warp_erosionNoise.DomainWarp(warpX, warpZ);
			double erosion = erosionNoise.GetNoise(warpX, warpZ);
			double height;

			if(erosion < 0)
			{
				if (noise < 0.3)
				{
					height = Remap(noise, -0.72, 0.3, 0, 32);
				}
				else if (noise < 0.4)
				{
					height = Remap(noise, 0.3, 0.4, 32, 58);
				}
				else height = Remap(noise, 0.4, 0.7, 58, 63);
			}

			else if(erosion < 0.5)
			{
				height = Remap(noise, -0.71, 0.7, 0, 50);
			}
			
			else height = Remap(noise, -0.71, 0.7, 0, 30);
			
			
			for (int i = 0; i < height; i++)
			{
				matrix[x][16 + i][z] = 0;
			}
		}
	}

	
}


void Chunk::Set_vertices(){

	vertex_list.reserve(9217);
	for (int i = 0; i < X_DIMENSION; i++) {
		for (int j = 0; j < Y_DIMENSION; j++) {
			for (int k = 0; k < Z_DIMENSION; k++) {
				if (matrix[i][j][k] != -1) {
					Blocks[matrix[i][j][k]].get_vertices(matrix, Coordinate(i + coordinate.x, j + coordinate.y, k + coordinate.z), coordinate, &vertex_list);
				}
			}
		}
	}
}


void Chunk::Create_mesh() {
	mesh = Mesh(vertex_list.data(), vertex_list.size() * sizeof(vertice));
}

void Chunk::Regenerate_mesh() {

	vertex_list.clear();

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				Blocks[matrix[i][j][k]].get_vertices(matrix, Coordinate(i + coordinate.x, j + coordinate.y, k + coordinate.z), coordinate, &vertex_list);
			}
		}
	}

	mesh.destroy();
	mesh = Mesh(vertex_list.data(), vertex_list.size() * sizeof(vertice));
}

void Chunk::Render(Shader& shader) {

	mesh.draw(shader, coordinate, vertex_list.size());
}

void Chunk::Destroy_block(Coordinate block_coordinate) {

	if (is_there_a_block(Coordinate(block_coordinate.x - coordinate.x, block_coordinate.y - coordinate.y, block_coordinate.z - coordinate.z))) {
		matrix[block_coordinate.x - coordinate.x][block_coordinate.y - coordinate.y][block_coordinate.z - coordinate.z] = EMPTY_BLOCK;
		Regenerate_mesh();
	}
}

bool Chunk::Near_from_player(glm::vec3 player_position, int distance){

	const int x_chunk = coordinate.x;
	const int z_chunk = coordinate.z;

	const int x_player = std::round(player_position.x / 16) * 16;
	const int z_player = std::round(player_position.z / 16) * 16;


	bool x_res, z_res;

	if (x_chunk < x_player) {
		x_res = (x_chunk + distance) >= x_player;
	}
	else x_res = (x_chunk - distance) <= x_player;

	if (z_chunk < z_player) {
		z_res = (z_chunk + distance) >= z_player;
	}
	else z_res = (z_chunk - distance) <= z_player;

	return x_res && z_res;
}

Chunk::~Chunk(){
	mesh.destroy();
}


