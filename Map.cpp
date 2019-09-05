#include "Map.h"
#include <iostream>
#include "ObjectPool.h"

Map::Map()
{
	texture = new aie::Texture("./bin/textures/Map.png");
}
Map::~Map() {
}
void Map:: draw(aie::Renderer2D* renderer){
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawSprite(texture, locationX, locationY);
}
void Map::update(float deltaTime, glm::vec2 loc) {
	
	locationX = loc.x; //sets the location of the map
	locationY = loc.y;//this will be relative to the players position when it is passed in
}
