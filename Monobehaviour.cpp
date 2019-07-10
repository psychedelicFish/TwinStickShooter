#include "Monobehaviour.h"
#include <iostream>

Monobehaviour::Monobehaviour(const char* FileName, int X, int Y) {
	texture = new aie::Texture(FileName);
	sizeX = (texture->getWidth() / X) * 30;
	sizeY = (texture->getHeight() / Y) * 30;
	frameX = X;
	frameY = Y;
}
Monobehaviour::~Monobehaviour() {
	delete texture;
}
bool Monobehaviour:: collision(Monobehaviour* other) {
	return position.x < other->position.x + other->sizeX &&		// Check left
		position.x  > other->position.x - other->sizeX &&				// Check right
		position.y < other->position.y + other->sizeY &&				// Check top
		position.y > other->position.y - other->sizeY;
}
void Monobehaviour::die() {
	std::cout << "dead" << std::endl;
}
void Monobehaviour:: update(float deltaTime) {}
void Monobehaviour:: draw(aie::Renderer2D* renderer) {}
glm::vec2 Monobehaviour::getPosition(){ return position; }
float Monobehaviour::getX() { return position.x; }
float Monobehaviour::getY() { return position.y; }
float Monobehaviour::getSizeX() { return sizeX; }
float Monobehaviour::getSizeY() { return sizeY; }