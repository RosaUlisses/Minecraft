#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "block.h"
#include "Coordinate.h"
#include "Shader.hpp"
#include "VAO.h"
#include "VBO.h"

class Mesh {

	public:

		VAO vao = VAO();
		VBO vbo = VBO(NULL, 0);

		Mesh(const void* vertices, GLuint size);

		void draw(Shader shader, Coordinate coordinate, int number_of_vertices);

		void destroy();

		void update_data(const void* vertices, GLuint size);
};


#endif
