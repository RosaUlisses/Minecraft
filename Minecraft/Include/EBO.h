#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {

	public:

		GLuint buffer;

		EBO(GLuint* indices, GLuint size);

		void bind();
		void unbind();
		void destroy();
		~EBO();
};




#endif