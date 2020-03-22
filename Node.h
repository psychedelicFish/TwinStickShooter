#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <Renderer2D.h>

struct Edge {
	class Node* target;
	float cost;
};

class Node {
private:
	float gscore;
	Node* parent;
	glm::vec2 position;

public:
	Node(glm::vec2 p, float score);

	std::vector<Edge> connections;
	void SetGScore(float score);
	float GetGScore();
	void SetParent(Node* p);
	Node* GetParent();
	void Draw(aie::Renderer2D* r); //for debuging
	glm::vec2 GetPosition();
};