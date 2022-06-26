#pragma once

#include <glad/glad.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    
    unsigned int shaderProgram;

    
    Shader(const char *vertexPath, const char *fragmentPath);
    
    
    void Activate();

    void setUniform1f(const char *name, GLfloat v0) const;
    void setUniform2f(const char *name, GLfloat v0, GLfloat v1) const;
    void setUniform3f(const char *name, GLfloat v0, GLfloat v1, GLfloat v2) const;
    void setUniform4f(const char *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;

    void setUniform1i(const char *name, GLint v0) const;
    void setUniform2i(const char *name, GLint v0, GLint v1) const;
    void setUniform3i(const char *name, GLint v0, GLint v1, GLint v2) const;
    void setUniform4i(const char *name, GLint v0, GLint v1, GLint v2, GLint v3) const;

    void setUniform1ui(const char *name, GLuint v0) const;
    void setUniform2ui(const char *name, GLuint v0, GLuint v1) const;
    void setUniform3ui(const char *name, GLuint v0, GLuint v1, GLuint v2) const;
    void setUniform4ui(const char *name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;

    void setUniform1fv(const char *name, GLsizei count, GLfloat *value) const;
    void setUniform2fv(const char *name, GLsizei count, GLfloat *value) const;
    void setUniform3fv(const char *name, GLsizei count, GLfloat *value) const;
    void setUniform4fv(const char *name, GLsizei count, GLfloat *value) const;

    void setUniform1iv(const char *name, GLsizei count, GLint *value) const;
    void setUniform2iv(const char *name, GLsizei count, GLint *value) const;
    void setUniform3iv(const char *name, GLsizei count, GLint *value) const;
    void setUniform4iv(const char *name, GLsizei count, GLint *value) const;

    void setUniform1uiv(const char *name, GLsizei count, GLuint *value) const;
    void setUniform2uiv(const char *name, GLsizei count, GLuint *value) const;
    void setUniform3uiv(const char *name, GLsizei count, GLuint *value) const;
    void setUniform4uiv(const char *name, GLsizei count, GLuint *value) const;

    void compileErrors(unsigned int shader, const char* type);
    
    void set_matrix4(const char* uniform, glm::mat4 matrix);
};
