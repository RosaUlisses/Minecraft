#include "Mesh.h"



Mesh::Mesh(const void* vertices, GLuint size) {

	vao = VAO();
	vao.bind();

	vbo = VBO(vertices, size);

	vao.link_atrrib_with_vbo(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.link_atrrib_with_vbo(vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	
	vao.unbind();
}



void Mesh::draw(Shader shader, Coordinate coordinate, int number_of_vertices) {

	vao.bind();
	glm::mat4 model = glm::mat4(1.0f);
	shader.set_matrix4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
	vao.unbind();

}

void Mesh::destroy() {

	vao.destroy();
	vbo.destroy();
}

void Mesh::update_data(const void* vertices, GLuint size) {

	vao.bind();

	vbo.uptade_data(vertices, size);

	vao.link_atrrib_with_vbo(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.link_atrrib_with_vbo(vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	vao.unbind();
	vao.unbind();
}