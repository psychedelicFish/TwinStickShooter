#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <list>
#include <Renderer2D.h>
#include <Texture.h>
#include <memory>

struct Tile;
using TileList = std::vector<std::shared_ptr<Tile>>;

class Node;
struct Tile;
class Pathfinder {
private:
	std::vector<Node*> nodes;
	int mapx;
	int mapy;
public:
	void AddNodeToList(Node* );
	std::list<Node*> findPath(Node* start, Node* end);
	Pathfinder(int x, int y);
	void Draw(aie::Renderer2D* r); //for debuging
	void SetUpEdges(const TileList &m);
	Node* ReturnNodeByIndex(int i);
	void ResetNodeGScores();
};