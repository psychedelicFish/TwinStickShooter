#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 pos, aie::Texture* t) : Monobehaviour(pos, 0, 0, glm::vec2{ 50,50})
{
	radius = getSizeX();
	texture = t;
	Active = false;
}
float Obstacle::getRadius() { return radius; }
void Obstacle::draw(aie::Renderer2D* renderer) {
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY);
}
void Obstacle::setPosition(float x, float y) {

	position.x = x;
	position.y = y;
}