#include "World.hpp"



World::World(FastNoiseLite continentalnessNoise, FastNoiseLite erosionNoise, FastNoiseLite warp_erosionNoise){

	for (int i = 0; i < 200; i += 16) {
		for (int j = 0; j < 200; j += 16) {
			
			insert_chunk(new Chunk(Coordinate(i, 0, j), continentalnessNoise, erosionNoise, warp_erosionNoise));
			insert_chunk(new Chunk(Coordinate(i, 0, -j), continentalnessNoise, erosionNoise, warp_erosionNoise));
			insert_chunk(new Chunk(Coordinate(-i, 0, j), continentalnessNoise, erosionNoise, warp_erosionNoise));
			insert_chunk(new Chunk(Coordinate(-i, 0, -j), continentalnessNoise, erosionNoise, warp_erosionNoise));
		}
	}


	for (auto it : chunks) {
		it.second->Set_vertices();
		it.second->Create_mesh();
	}

}


void World::insert_chunk(Chunk* chunk) {

	chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
}

void World::insert_chunk(Coordinate coordinate, Chunk* chunk) {

	chunks.insert(std::pair<Coordinate, Chunk*>(coordinate, chunk));
}

void World::remove_chunk(Coordinate chunk_coordinate) {
	chunks.erase(chunk_coordinate);
}

void World::render(Shader& shader, glm::vec3 position) {

	for (auto it : chunks) {
		if (it.second->Near_from_player(position, 100)) {
			it.second->Render(shader);
		}
	}
}

Chunk* World::get_chunk(Coordinate coordinate) {

	int x = (coordinate.x / X_DIMENSION) * X_DIMENSION;
	int y = (coordinate.y / Y_DIMENSION) * Y_DIMENSION;
	int z = (coordinate.z / Z_DIMENSION) * Z_DIMENSION;

	

	Coordinate chunk_coordinate = Coordinate(x, y, z);

	ChunkMap::iterator chunk = chunks.find(chunk_coordinate);

	if (chunk != chunks.end()) {
		return chunk->second;
	}

	return nullptr;
}

void World::destroy_block(Coordinate block_coordinate) {

	Chunk* chunk = get_chunk(block_coordinate);
    chunk->Destroy_block(block_coordinate);
}

World::~World(){
	for(auto chunk : chunks){
		delete chunk.second;
	}
}

