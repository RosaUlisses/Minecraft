#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "Shader.hpp"
#include "Camera.h"
#include "coordinate.h"
#include "chunk.h"
#include "World.h"
#include "block.h"

#define WIDTH  600
#define HEIGHT  600


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void init_opengl() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main(int argc, const char** argv) {

    init_opengl();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }




    Shader shaders("res/VertexShader.vert", "res/FragmentShader.frag");

 
    GLuint uniID = glGetUniformLocation(shaders.shaderProgram, "scale");
  

    Texture tex("res/atlas.png");
    tex.bind();


    glEnable(GL_DEPTH_TEST);
    shaders.Activate();

    Camera camera(100, 100);
    
    Chunk my_chunk = Chunk(1, 1, 1);
    
    my_chunk.create_mesh();
    

    World world = World();
   
  

    while (!glfwWindowShouldClose(window)) {

        
        processInput(window);

        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders.Activate();

       
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        
        camera.Inputs_mouse(window, &world);
        camera.Inputs_keyboard(window);
       
        //world.generate_new_chunks(camera.position, camera.previous_position);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaders, "camMatrix");
        
        world.render(shaders);
        
        //printf("%f %f %f\t%f %f %f\n", camera.position.x, camera.position.y, camera.position.z, camera.previous_position.x, camera.previous_position.y, camera.previous_position.z);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}