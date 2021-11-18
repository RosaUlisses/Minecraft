#ifndef CHUNK_H
#define CHUNK_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "block.h"
#include "Shader.hpp"
#include "Coordinate.h"
#include "Mesh.h"




#define EMPTY_BLOCK -1


class Chunk {

	public:

		std::vector<vertice> vertex_list;

		Coordinate coordinate = Coordinate(0, 0, 0);
		Mesh mesh = Mesh(NULL, 0);
		int matrix[X_DIMENSION][Y_DIMENSION][Z_DIMENSION];
		
		bool is_there_a_block(Coordinate coordinate);

		Chunk(int x, int y, int z);

		void create_mesh();

		void set_mesh_state(bool state);

		void regenerate_mesh();
	
		void render(Shader shader);

		void destroy_block(Coordinate block_coordinate);

		
};


#endif