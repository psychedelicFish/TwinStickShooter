#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <list>
#include <Renderer2D.h>
#include <Texture.h>

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

struct Tile;
class Pathfinder {
private:
	std::vector<Node*> nodes;
	int mapx;
	int mapy;
public:
	void AddNodeToList(Node* n);
	std::list<Node*> findPath(Node* start, Node* end);
	Pathfinder(int x, int y);
	void Draw(aie::Renderer2D* r); //for debuging
	void SetUpEdges(const std::vector<Tile*> &m);
	Node* ReturnNodeByIndex(int i);
	void ResetNodeGScores();
};