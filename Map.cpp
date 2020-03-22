#include "Map.h"
#include "Pathfinding.h"
#include <iostream>
#include "ObjectPool.h"
#include "Node.h"

Map::Map()
{
	pathfinder = new Pathfinder(mapWidth,mapHeight);
	for (int i = 0; i < mapWidth * mapHeight; i++) {
		if (m[i] == 0) {
			std::shared_ptr<Tile> tile(new PassableTile(glm::vec2(i % mapWidth * tileSizeX, (int)(i / mapHeight) * tileSizeY)));
			map.push_back(tile);

			glm::vec2 nodePosition = { tile->position.x, tile->position.y };
			auto node = new Node(nodePosition, 100000.f);

			pathfinder->AddNodeToList(node);
		}
		else {
			std::shared_ptr<Tile> tile(new ImpassableTile(glm::vec2(i % mapWidth * tileSizeX, (int)(i / mapHeight) * tileSizeY)));
			map.push_back(tile);
			glm::vec2 nodePosition = { tile->position.x, tile->position.y };
			auto node = new Node(nodePosition, 100000.f);

			pathfinder->AddNodeToList(node);
		}
	}
	pathfinder->SetUpEdges(map);
}


Map::~Map() {
}
void Map:: draw(aie::Renderer2D* renderer){
	
	for(auto n : map) {
		n->Draw(renderer);
	}
}
void Map::update(float deltaTime, glm::vec2 loc) {
	
	locationX = loc.x; //sets the location of the map
	locationY = loc.y; //this will be relative to the players position when it is passed in
	
}

std::list<Node*> Map::QueryPathfinder(glm::vec2 pos1, glm::vec2 pos2) {
	Node* i = CalculateNode(pos1);
	Node* j = CalculateNode(pos2);
	
	return pathfinder->findPath(i, j);
}

Node* Map::CalculateNode(glm::vec2 position) {
	
	//glm::vec2 position = { tileSizeX * ((int)(pos.x / tileSizeX)), tileSizeY * ((int)(pos.y / tileSizeY)) };
	const int row = position.y / tileSizeY;
	const int column = position.x / tileSizeX;
	
	if (row < 0 || row >= mapHeight || column < 0 || column >= mapWidth) {
		return nullptr;
	}
	
	int index = row * mapWidth + column;
	
	return pathfinder->ReturnNodeByIndex(index);
}

bool Map::CheckIfPassable(glm::vec2 position) {
	//glm::vec2 position = { tileSizeX * ((int)(pos.x / tileSizeX)), tileSizeY * ((int)(pos.y / tileSizeY)) };
	
	const int row = glm::ceil((position.y - tileSizeY/2) / tileSizeY);
	const int column = glm::ceil((position.x - tileSizeX/2) / tileSizeX);

	if (row < 0 || row >= mapHeight || column < 0 || column >= mapWidth) {
		return nullptr;
	}

	int index = row * mapWidth + column;
	if (map[index]->passable) {
		return true;
	}
	else {
		return false;
	}

	//return map[index]->passable;
}
