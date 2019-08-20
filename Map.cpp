#include "Map.h"

Map::Map()
{
	texture = new aie::Texture("./bin/textures/Map.png");
}

void Map:: draw(aie::Renderer2D* renderer){
	renderer->drawSprite(texture, 720 / 2, 720 / 2);
}
