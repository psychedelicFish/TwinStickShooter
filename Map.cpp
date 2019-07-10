#include "Map.h"

Mape::Mape()
{
	texture = new aie::Texture("../bin/textures/Map.png");
}

void Mape:: draw(aie::Renderer2D* renderer){
	renderer->drawSprite(texture, 720 / 2, 720 / 2);
}
