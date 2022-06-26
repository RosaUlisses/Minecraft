#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <thread>
#include <cmath>
#include <mutex>
#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Thread_Safe_Queue.h"
#include "Chunk.hpp"
#include "World.hpp"
#include "Block.hpp"
#include "FastNoiseLite.h"

#define WIDTH  600
#define HEIGHT  600


bool terminate_thread = false;
FastNoiseLite continentalnessNoise;
FastNoiseLite erosionNoise, warp_erosionNoise;


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


void update_Chunks(Queue* queue){
    while(!terminate_thread){
        if(!queue->chunks_to_create.empty()){
            while(!queue->chunks_to_create.empty()){
                Coordinate coordinate = queue->chunks_to_create.front();
                queue->chunks_to_create.pop_front();
                Chunk* chunk = new Chunk(Coordinate(coordinate.x, coordinate.y, coordinate.z), continentalnessNoise, erosionNoise, warp_erosionNoise);
                chunk->Set_vertices();
                queue->Push_in_ready(chunk);
            }
        }

    }
}

int MAX = 16;

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

 
    erosionNoise.SetSeed(139);
    erosionNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    erosionNoise.SetFrequency(0.001);
    erosionNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    erosionNoise.SetFractalOctaves(4);
    erosionNoise.SetFractalLacunarity(3.00);
    erosionNoise.SetFractalGain(1.00);
    erosionNoise.SetFractalWeightedStrength(0.30);
    erosionNoise.SetFractalPingPongStrength(5.00);
    erosionNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    erosionNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
    erosionNoise.SetCellularJitter(1.00);
    warp_erosionNoise.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    warp_erosionNoise.SetDomainWarpAmp(300);
    warp_erosionNoise.SetFrequency(0.0005);
    warp_erosionNoise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    warp_erosionNoise.SetFractalOctaves(8);
    warp_erosionNoise.SetFractalLacunarity(2.50);
    warp_erosionNoise.SetFractalGain(0.65);

    
    continentalnessNoise.SetSeed(11);
    continentalnessNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    continentalnessNoise.SetFrequency(0.008);
    continentalnessNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
    continentalnessNoise.SetFractalOctaves(1);
    continentalnessNoise.SetFractalLacunarity(2.50);
	continentalnessNoise.SetFractalGain(0.25);
    continentalnessNoise.SetFractalWeightedStrength(0.00);


    Shader shaders("res/VertexShader.vert", "res/FragmentShader.frag");
    GLuint uniID = glGetUniformLocation(shaders.shaderProgram, "scale");
    Texture tex("res/atlas.png");
    tex.bind();
    glEnable(GL_DEPTH_TEST);
    shaders.Activate();
    Camera camera(100, 100);

    World world = World(continentalnessNoise, erosionNoise, warp_erosionNoise);

    Queue chunks_to_create;
    Queue chunks_to_delete;

    std::thread thread(update_Chunks, &chunks_to_create);

    while (!glfwWindowShouldClose(window)) {


        processInput(window);
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders.Activate();

        camera.Inputs_mouse(window, &world);
        camera.Inputs_keyboard(window);


        camera.Matrix(45.0f, 0.1f, 100.0f, shaders, "camMatrix");

        
        printf("%f | %f | %f\n", camera.position.x, camera.position.y, camera.position.z);

        world.render(shaders, camera.position);

        if (chunks_to_create.Are_chunks_ready()) {
            chunks_to_create.Pop(world);
        }


        if (camera.Player_changed_chunk(world)) {
            for (int i = -5; i < 5; i++) {
                for (int j = -5; j < 5; j++) {
                    if (world.get_chunk(Coordinate(std::round(camera.position.x / 16) * 16 + (i * 16), 0, std::round(camera.position.z / 16) * 16 + (j * 16))) == nullptr) {
                        chunks_to_create.Push(Coordinate(std::round(camera.position.x / 16) * 16 + (i * 16), 0, std::round(camera.position.z / 16) * 16 + (j * 16)));
                    }
                }
            }

            for (auto it : world.chunks) {
                if (!it.second->Near_from_player(camera.position, 150)) {
                    delete it.second;
                    world.remove_chunk(it.first);
                }
            }
            
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminate_thread = true;
    glfwTerminate();

    exit(0);
}