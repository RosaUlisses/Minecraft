#include "VBO.h"

VBO::VBO(const void* vertices, GLuint size) {

	glGenBuffers(1, &(buffer));
	glBindBuffer(GL_ARRAY_BUFFER, VBO::buffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}



void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy() {
	glDeleteBuffers(1, &(buffer));
}

void VBO::uptade_data(const void* vertices, GLuint size) {

	bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

