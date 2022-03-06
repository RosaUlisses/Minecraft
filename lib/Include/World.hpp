#ifndef WORLD_H
#define WORLD_H

#include <mutex>
#include <unordered_map>
#include <iterator>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Chunk.hpp"
#include "Coordinate.h"

#define RENDER_DISTANCE    100

typedef std::unordered_map<Coordinate, Chunk*, Coordinate::HahsFunction> ChunkMap;

class World {

	public:
		ChunkMap chunks;

		World(FastNoiseLite continentalnessNoise, FastNoiseLite erosionNoise, FastNoiseLite warp_erosionNoise);
		void insert_chunk(Chunk* chunk);
		void insert_chunk(Coordinate coordinate, Chunk* chunk);
		void remove_chunk(Coordinate chunk_coordinate);
		void render(Shader& shader, glm::vec3 position);
		void destroy_block(Coordinate block_coordinate);
		Chunk* get_chunk(Coordinate coordinate);
		~World();


};




#endif