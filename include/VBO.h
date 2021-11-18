#ifndef VBO_H
#define VBO_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>


class VBO {

public:

	GLuint buffer;
	VBO(const void* vertices, GLuint size);
	void bind();
	void unbind();
	void destroy();
	void uptade_data(const void* vertices, GLuint size);
};



#endif