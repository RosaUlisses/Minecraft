#ifndef VAO_H
#define VAO_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"


class VAO {

public:
	GLuint buffer;

	VAO();
	void bind();
	void unbind();
	void link_atrrib_with_vbo(VBO& vbo, GLuint layout, GLuint num_componetes, GLenum type, GLsizeiptr stride, void* offset);
	void destroy();
	

};




#endif