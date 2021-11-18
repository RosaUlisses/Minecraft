#include "World.h"


World::World() {

	for (int i = 0; i < 100; i += 16) {
		for (int j = 0; j < 100; j += 16) {
			Chunk* chunk = new Chunk(i, 0, j);
			chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
		}
		for (int j = 0; j > -100; j -= 16) {
			Chunk* chunk = new Chunk(i, 0, j);
			chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
		}
	}

	for (int i = 0; i > -100; i -= 16) {
		for (int j = 0; j < 100; j += 16) {
			Chunk* chunk = new Chunk(i, 0, j);
			chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
		}
		for (int j = 0; j > -100; j -= 16) {
			Chunk* chunk = new Chunk(i, 0, j);
			chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
		}
	}


}

void World::insert_chunk(Chunk* chunk) {

	chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
}

void World::remove_chunk(Coordinate chunk_coordinate) {

	chunks.erase(chunk_coordinate);
}

void World::render(Shader shader) {

	ChunkMap::iterator item = chunks.begin();

	for (item; item != chunks.end(); item++) {
		Chunk* chunk = item->second;
		chunk->render(shader);
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

    chunk->destroy_block(block_coordinate);
}

void World::generate_new_chunks(glm::vec3 position, glm::vec3 previous_position) {

	int x = (position.x / X_DIMENSION) * X_DIMENSION;
	if (position == previous_position) {
		return;
	}

	for (int i = x; i < x + RENDER_DISTANCE; i += 16) {
		for (int j = 0; j < 100; j += 16) {
			Chunk* chunk = get_chunk(Coordinate(i, 0, j));
			if (chunk == nullptr) {
				Chunk* chunk = new Chunk(i, 0, j);
				chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
			}
		}
		for (int j = 0; j > -100; j -= 16) {
			Chunk* chunk = get_chunk(Coordinate(i, 0, j));
			if (chunk == nullptr) {
				Chunk* chunk = new Chunk(i, 0, j);
				chunks.insert(std::pair<Coordinate, Chunk*>(chunk->coordinate, chunk));
			}
		}
	}

}