
#include "Camera.hpp"


bool firstMouse = false;
float last_X = 300.0f;
float last_Y = 300.0f;
float yaw = -90.0f;	
float pitch = 0.0f;
float fov = 45.0f;
glm::vec3 new_orientation;

World* world;
Camera* camera;
Coordinate* look_at;


void mouse_callback(GLFWwindow* window, double xpos, double ypos){

    if (firstMouse){
        last_X = xpos;
        last_Y = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - last_X;
    float yoffset = last_Y - ypos;
    last_X = xpos;
    last_Y = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_orientation = glm::normalize(direction);
    camera->orientation = new_orientation;
}

void Camera::ray_casting() {

    glm::vec3 end = orientation * 5.0f;


    glm::vec3 pos = position;

    glm::vec3 delta_x = end / glm::abs(end.x);
    glm::vec3 delta_y = end / glm::abs(end.y);
    glm::vec3 delta_z = end / glm::abs(end.z);

    glm::vec3 x_distance = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 y_distance = glm::vec3(0.0f, 0.0f, 0.0f);;
    glm::vec3 z_distance = glm::vec3(0.0f, 0.0f, 0.0f);;

    if (position.x > 0) {
        x_distance.x = glm::ceil(position.x) - position.x;
    }
    else {
        x_distance.x = glm::floor(position.x) - position.x;
    }
    x_distance.y = delta_x.y * glm::abs(x_distance.x);
    x_distance.z = delta_x.z * glm::abs(x_distance.x);


    if (position.y > 0) {
        y_distance.y = glm::ceil(position.y) - position.y;
    }
    else {
        y_distance.y = glm::floor(position.y) - position.y;
    }
    y_distance.x = delta_y.x * glm::abs(y_distance.y);
    y_distance.z = delta_y.z * glm::abs(y_distance.y);


    if (position.z > 0) {
        z_distance.z = glm::ceil(position.z) - position.z;
    }
    else {
        z_distance.z = glm::floor(position.z) - position.z;
    }
    z_distance.x = delta_z.x * glm::abs(z_distance.z);
    z_distance.y = delta_z.y * glm::abs(z_distance.z);


    Coordinate look_at_block = Coordinate(0, 0, 0);
    
    for (int i = 0; i < 10; i++) {

        if (glm::length(x_distance) < glm::length(y_distance) && glm::length(x_distance) < glm::length(y_distance)) {

            x_distance += delta_x;

            look_at_block = Coordinate((position.x + x_distance.x), (position.y + x_distance.y), (position.z + x_distance.z));
            if (orientation.x < 0) look_at_block.x--;

            Chunk* chunk = world->get_chunk(look_at_block);
            
            if (chunk == nullptr) {
                look_at = nullptr;
                return;
            }

            if (chunk->is_there_a_block(look_at_block)) {
                look_at = new Coordinate (look_at_block);
                return;
            }
        }

        else if (glm::length(y_distance) < glm::length(x_distance) && glm::length(y_distance) < glm::length(z_distance)) {
            y_distance += delta_y;
            
            look_at_block = Coordinate((position.x + y_distance.x), (position.y + y_distance.y), (position.z + y_distance.z));
            if (orientation.y < 0) look_at_block.y--;
            
            Chunk* chunk = world->get_chunk(Coordinate(look_at_block));
            
            if (chunk == nullptr) {
                look_at = nullptr;
                return;
            }

            if (chunk->is_there_a_block(look_at_block)) {
                look_at = new Coordinate(look_at_block);
                return;
            }
        }

        else {
            z_distance += delta_z;
            
            look_at_block = Coordinate((position.x + z_distance.x), (position.y + z_distance.y), (position.z + z_distance.z));

            if (orientation.z < 0) look_at_block.z--;

            Chunk* chunk = world->get_chunk(look_at_block);

            if (chunk == nullptr) {
                look_at = nullptr;
                return;
            }

            if (chunk->is_there_a_block(look_at_block)) {
                look_at = new Coordinate(look_at_block);
                return;
            }
        }
    }

    look_at = nullptr;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        camera->ray_casting();
        if (look_at != nullptr) {
            world->destroy_block(*look_at);
        }   
    }
}

Camera::Camera(int height, int width) {

	Camera::height = height;
	Camera::width = width;
	Camera::position = position;
}

void Camera::Matrix(float FOV_deg, float near_plane, float far_plane, Shader& shader, const char* uniform) {

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Camera::position, Camera::position + Camera::orientation, Camera::up_orientation);
    shader.set_matrix4("view", view);
	projection = glm::perspective(glm::radians(FOV_deg), (float)(Camera::width / Camera::height), near_plane, far_plane);
    shader.set_matrix4("proj", projection);
   
}



void Camera::Inputs_keyboard(GLFWwindow* window) {

    Camera::previous_position = Camera::position;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Camera::position += Camera::speed * Camera::orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Camera::position += Camera::speed * -(glm::normalize(glm::cross(Camera::orientation, Camera::up_orientation)));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Camera::position += Camera::speed * - (Camera::orientation);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Camera::position += Camera::speed * (glm::normalize(glm::cross(Camera::orientation, Camera::up_orientation)));
	}
}

void Camera::Inputs_mouse(GLFWwindow* window, World* world_terrain) {
    world = world_terrain;
    camera = this;
  
}

bool Camera::Player_changed_chunk(World& world){
    if (world.get_chunk(Coordinate(previous_position.x, 0, previous_position.z))
        != world.get_chunk(Coordinate(position.x, 0, position.z))) {
        return true;
    }
    return false;
}
