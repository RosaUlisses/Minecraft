#include <Shader.hpp>

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertex_file, const char* fragment_file) {

	std::string vertex_code = get_file_contents(vertex_file);
	std::string fragment_code = get_file_contents(fragment_file);

	const char* vertex_src = vertex_code.c_str();
	const char* fragment_src = fragment_code.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertex_src, NULL);

	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX");


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragment_src, NULL);

	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, "FRAGMENT");


	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	compileErrors(shaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate() {
    glUseProgram(shaderProgram);
}

void Shader::setUniform1f(const char *name, GLfloat v0) const {
	glUniform1f(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform2f(const char *name, GLfloat v0, GLfloat v1) const {
	glUniform2f(glGetUniformLocation(shaderProgram, name), v0, v1);
}

void Shader::setUniform3f(const char *name, GLfloat v0, GLfloat v1, GLfloat v2) const {
	glUniform3f(glGetUniformLocation(shaderProgram, name), v0, v1, v2);
}

void Shader::setUniform4f(const char *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
	glUniform4f(glGetUniformLocation(shaderProgram, name), v0, v1, v2, v3);
}


void Shader::setUniform1i(const char *name, GLint v0) const {
	glUniform1i(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform2i(const char *name, GLint v0, GLint v1) const {
	glUniform2i(glGetUniformLocation(shaderProgram, name), v0, v1);
}

void Shader::setUniform3i(const char *name, GLint v0, GLint v1, GLint v2) const {
	glUniform3i(glGetUniformLocation(shaderProgram, name), v0, v1, v2);
}

void Shader::setUniform4i(const char *name, GLint v0, GLint v1, GLint v2, GLint v3) const {
	glUniform4i(glGetUniformLocation(shaderProgram, name), v0, v1, v2, v3);
}


void Shader::setUniform1ui(const char *name, GLuint v0) const {
	glUniform1ui(glGetUniformLocation(shaderProgram, name), v0);
}

void Shader::setUniform2ui(const char *name, GLuint v0, GLuint v1) const {
	glUniform2ui(glGetUniformLocation(shaderProgram, name), v0, v1);
}

void Shader::setUniform3ui(const char *name, GLuint v0, GLuint v1, GLuint v2) const {
	glUniform3ui(glGetUniformLocation(shaderProgram, name), v0, v1, v2);
}

void Shader::setUniform4ui(const char *name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
	glUniform4ui(glGetUniformLocation(shaderProgram, name), v0, v1, v2, v3);
}


void Shader::setUniform1fv(const char *name, GLsizei count, GLfloat *value) const {
	glUniform1fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2fv(const char *name, GLsizei count, GLfloat *value) const {
	glUniform2fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3fv(const char *name, GLsizei count, GLfloat *value) const {
	glUniform3fv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4fv(const char *name, GLsizei count, GLfloat *value) const {
	glUniform4fv(glGetUniformLocation(shaderProgram, name), count, value);
}


void Shader::setUniform1iv(const char *name, GLsizei count, GLint *value) const {
	glUniform1iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2iv(const char *name, GLsizei count, GLint *value) const {
	glUniform2iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3iv(const char *name, GLsizei count, GLint *value) const {
	glUniform3iv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4iv(const char *name, GLsizei count, GLint *value) const {
	glUniform4iv(glGetUniformLocation(shaderProgram, name), count, value);
}


void Shader::setUniform1uiv(const char *name, GLsizei count, GLuint *value) const {
	glUniform1uiv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform2uiv(const char *name, GLsizei count, GLuint *value) const {
	glUniform2uiv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform3uiv(const char *name, GLsizei count, GLuint *value) const {
	glUniform3uiv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::setUniform4uiv(const char *name, GLsizei count, GLuint *value) const {
	glUniform4uiv(glGetUniformLocation(shaderProgram, name), count, value);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

void Shader::set_matrix4(const char* uniform, glm::mat4 matrix) {

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}
