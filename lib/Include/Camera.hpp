#ifndef CAMERA_H
#define CAMERA_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "Chunk.hpp"
#include "World.hpp"

class Camera {

	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 previous_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up_orientation = glm::vec3(0.0f, 1.0f, 0.0f);

		int height;
		int width;

		float speed = 0.1f;
		float sensitivity = 0.5f;

		Camera(int height, int width);

		void Matrix(float FOV_deg, float near_plane, float far_plane, Shader& shader, const char* uniform);

		void ray_casting();

		void Inputs_keyboard(GLFWwindow* window);

		void Inputs_mouse(GLFWwindow* window, World* world_terrain);

		bool Player_changed_chunk(World& world);
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif 