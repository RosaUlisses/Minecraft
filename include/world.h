#ifndef WORLD_H
#define WORLD_H


#include <unordered_map>
#include <iterator>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "chunk.h"
#include "Coordinate.h"

#define RENDER_DISTANCE    100

typedef std::unordered_map<Coordinate, Chunk*, Coordinate::HahsFunction> ChunkMap;

class World {

	public:
		ChunkMap chunks;

		World();

		void insert_chunk(Chunk* chunk);
		void remove_chunk(Coordinate chunk_coordinate);
		void render(Shader shader);
		void destroy_block(Coordinate block_coordinate);
		Chunk* get_chunk(Coordinate coordinate);

		void update_world(glm::vec3 player_position);
		void generate_new_chunks(glm::vec3 position, glm::vec3 previous_position);
		void destoy_old_chunks(glm::vec3 player_position);

};




#endif