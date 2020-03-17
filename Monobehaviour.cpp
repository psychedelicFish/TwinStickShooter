#include "Monobehaviour.h"
#include <iostream>

Monobehaviour::Monobehaviour(glm::vec2 pos, char* FileName, int X, int Y, glm::vec2 size) {
	texture = new aie::Texture(FileName);
	sizeX = size.x;
	sizeY = size.y;
	frameX = X;
	frameY = Y;
	position = pos;
}
Monobehaviour::Monobehaviour(glm::vec2 pos, int X, int Y, glm::vec2 size) {
	sizeX = size.x;
	sizeY = size.y;
	frameX = X;
	frameY = Y;
	position = pos;
}
Monobehaviour::~Monobehaviour() {
}
bool Monobehaviour:: collision(std::shared_ptr<Monobehaviour> other) {
	return position.x < other->position.x + other->sizeX &&		// Check left
		position.x  > other->position.x - other->sizeX &&				// Check right
		position.y < other->position.y + other->sizeY &&				// Check top
		position.y > other->position.y - other->sizeY;
}
void Monobehaviour::die() {
	//std::cout << "dead" << std::endl;
}
void Monobehaviour:: update(float deltaTime) {}
void Monobehaviour:: draw(aie::Renderer2D* renderer) {
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY);
}
glm::vec2 Monobehaviour::getPosition(){ return position; }
float Monobehaviour::getX() { return position.x; }
float Monobehaviour::getY() { return position.y; }
float Monobehaviour::getSizeX() { return sizeX; }
float Monobehaviour::getSizeY() { return sizeY; }