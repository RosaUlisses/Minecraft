#include "VAO.h"

VAO::VAO() {

	glGenVertexArrays(1, &(VAO::buffer));
}

void VAO::bind() {
	glBindVertexArray(VAO::buffer);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::link_atrrib_with_vbo(VBO& vbo, GLuint layout, GLuint num_componets, GLenum type, GLsizeiptr stride, void* offset) {

	vbo.bind();

	glVertexAttribPointer(layout, num_componets, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	vbo.unbind();
}

void VAO::destroy() {
	glDeleteVertexArrays(1, &(VAO::buffer));
}