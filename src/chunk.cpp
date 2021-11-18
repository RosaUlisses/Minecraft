
#include "chunk.h"

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


Chunk::Chunk(int x, int y, int z) {

	for (int i = 0; i < X_DIMENSION; i++) {
		for (int j = 0; j < Y_DIMENSION; j++) {
			for (int k = 0; k < Z_DIMENSION; k++) {
				if (j == 0) matrix[i][j][k] = 0;
				else if (j == 15) matrix[i][j][k] = 1;
				else if (j >= 11) matrix[i][j][k] = 3;
				else if(j < 11) matrix[i][j][k] = 2;
				
			}
		}
	}
	coordinate = Coordinate(x, y, z);
	create_mesh();
}

void Chunk::create_mesh() {

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {

				std::vector<vertice> vertices_of_block;
				vertices_of_block = Blocks[matrix[i][j][k]].get_vertices(matrix, Coordinate(i + coordinate.x, j + coordinate.y , k + coordinate.z), coordinate);
				vertex_list.insert(vertex_list.begin(), vertices_of_block.begin(), vertices_of_block.end());
				
			}
		}
	}

	mesh = Mesh(vertex_list.data(), vertex_list.size() * sizeof(vertice));
}

void Chunk::regenerate_mesh() {

	vertex_list.clear();

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {

				std::vector<vertice> vertices_of_block;

				vertices_of_block = Blocks[matrix[i][j][k]].get_vertices(matrix, Coordinate(i + coordinate.x, j + coordinate.y, k + coordinate.z), coordinate);
				vertex_list.insert(vertex_list.begin(), vertices_of_block.begin(), vertices_of_block.end());
			}
		}
	}

	mesh.destroy();
	mesh = Mesh(vertex_list.data(), vertex_list.size() * sizeof(vertice));
}

void Chunk::render(Shader shader) {

	mesh.draw(shader, coordinate, vertex_list.size());
}

void Chunk::destroy_block(Coordinate block_coordinate) {

	if (is_there_a_block(Coordinate(block_coordinate.x - coordinate.x, block_coordinate.y - coordinate.y, block_coordinate.z - coordinate.z))) {
		matrix[block_coordinate.x - coordinate.x][block_coordinate.y - coordinate.y][block_coordinate.z - coordinate.z] = EMPTY_BLOCK;
		regenerate_mesh();
	}
}