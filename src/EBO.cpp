#include "EBO.h"

EBO::EBO(GLuint* indices, GLuint size) {
	glGenBuffers(1, &(EBO::buffer));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO::buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO::buffer);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() {
	glDeleteBuffers(1, &(EBO::buffer));
}