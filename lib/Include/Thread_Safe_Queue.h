#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <deque>
#include <mutex>
#include "Chunk.hpp"
#include "World.hpp"
#include "Coordinate.h"


class Queue {


	public:

		std::mutex mutex;
		std::deque<Coordinate> chunks_to_create;

		std::mutex mutex_2;
		std::deque<Chunk*> ready;

		void Pop(World& world);
		void Push(Coordinate coordinate);
		void Push_in_ready(Chunk* chunk);
		bool Are_chunks_ready();
		void Update();
};


#endif
