#pragma once
#include <queue>
#include "Pathfinding.h"

//Creating our own Queue so we can iterate through the underlying container
class Queue : public std::priority_queue<Node*> {
public:
	using type = typename std::priority_queue<Node*>::container_type;

	typename type::iterator begin() { //Allows us to find the beginning
		return c.begin();
	}
	typename type::iterator end() { //Allows us to grab the end 
		return c.end();
	}

};

