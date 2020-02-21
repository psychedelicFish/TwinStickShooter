#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <list>
#include <Renderer2D.h>
#include <Texture.h>

struct Edge {
	Node* target;
	float cost;
};

class Node {
private:
	glm::vec2 position;
	
	aie::Texture* passableTexture = new aie::Texture("./bin/textures/Map_Passable.png");
	aie::Texture* impassableTexture = new aie::Texture("./bin/textures/Map_Impassable.png");
	float gscore;
	Node* parent;
	
	bool passable;

public:
	Node(glm::vec2 p, bool pass);
	
	std::vector<Edge> connections;
	void SetGScore(int score);
	float GetGScore();
	void SetParent(Node* p);
	Node* GetParent();
	void Draw(aie::Renderer2D* r);


	bool operator()(Node* i, Node* j) { return (i->gscore < j->gscore); }
	
};

class Pathfinder {
	std::list<Node*> findPath(Node* start, Node* end);
};