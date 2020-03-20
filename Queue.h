#pragma once
#include <queue>

template<typename Q>
class Queue : public std::priority_queue<Q> {
public:
	using type = typename std::priority_queue<Q>::container_type;

	typename type::iterator begin() {
		return c.begin();
	}
	typename type::iterator end() {
		return c.end();
	}

};

