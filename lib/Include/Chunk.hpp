#ifndef CHUNK_H
#define CHUNK_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Block.hpp"
#include "Shader.hpp"
#include "Coordinate.h"
#include "Mesh.h"
#include "FastNoiseLite.h"




#define EMPTY_BLOCK -1


class Chunk {

	public:

		std::vector<vertice> vertex_list;

		Coordinate coordinate = Coordinate(0, 0, 0);
		Mesh mesh = Mesh(NULL, 0);
		int matrix[X_DIMENSION][Y_DIMENSION][Z_DIMENSION];
		
		bool is_there_a_block(Coordinate coordinate);

		Chunk(int x, int y, int z);

		Chunk(Coordinate coordinate, FastNoiseLite continentalnessNoise, FastNoiseLite erosionNoise, FastNoiseLite warp_erosionNoise);

		void Set_vertices();
		void Create_mesh();
		void Set_mesh_state(bool state);
		void Regenerate_mesh();
		void Render(Shader& shader);
		void Destroy_block(Coordinate block_coordinate);
		bool Near_from_player(glm::vec3 player_position, int distance);
		~Chunk();
};


#endif