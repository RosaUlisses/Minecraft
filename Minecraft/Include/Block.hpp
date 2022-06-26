#ifndef BLOCK_H
#define BLOCK_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "Coordinate.h"


#define X_DIMENSION    16
#define Y_DIMENSION    80
#define Z_DIMENSION    16

struct vertice {

	glm::vec3 points = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 texture = glm::vec3(0.0f, 0.0f, 0.0f);

};


class Block {

	public:

		std::vector<vertice> vertices;
		std::string ID;


		void init_vertices();

		void set_texture(int texture_offset, int position);

		Block(std::string ID, int vertical_offset, int horizontal_offset);

		Block(std::string ID, int texture_offset);

		Block(std::string ID, int up_offset, int down_offset, int horizontal_offset);

		void add_face(std::vector<vertice>* vertex_list, Coordinate coordinate, int face);

		void get_vertices(int matrix[X_DIMENSION][Y_DIMENSION][Z_DIMENSION], Coordinate coordinate, Coordinate chunk_coordinate, std::vector<vertice>* vertex_list);

};


#endif