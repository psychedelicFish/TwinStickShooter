#include "Map.h"
#include "Pathfinding.h"
#include <iostream>
#include "ObjectPool.h"

Map::Map()
{
	for (int i = 0; i <= 48; i++) {
		auto node = new Node(glm::vec2(i % 22, (int)i / 22), true);
	}
	//texture = new aie::Texture("./bin/textures/Map.png");
}
Map::~Map() {
}
void Map:: draw(aie::Renderer2D* renderer){
	
	renderer->setUVRect(0, 0, 1, 1);
	for each(Node* n in map) {
		n->Draw(renderer);
	}
}
void Map::update(float deltaTime, glm::vec2 loc) {
	
	locationX = loc.x; //sets the location of the map
	locationY = loc.y;//this will be relative to the players position when it is passed in
}
