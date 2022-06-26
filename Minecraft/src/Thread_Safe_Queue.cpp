#include "Thread_Safe_Queue.h"


void Queue::Push(Coordinate coordinate){
	std::lock_guard<std::mutex> lock(mutex);
	chunks_to_create.push_back(coordinate);
}

void Queue::Pop(World& world){
	std::lock_guard<std::mutex> lock(mutex_2);
	while(!ready.empty()){
		Chunk* chunk = ready.front();
		ready.pop_front();
		chunk->Create_mesh();
		world.insert_chunk(chunk);
	}
}

void Queue::Push_in_ready(Chunk* chunk){
	std::lock_guard<std::mutex> lock(mutex_2);
	ready.push_back(chunk);
}


bool Queue::Are_chunks_ready(){
	return !ready.empty();
}



