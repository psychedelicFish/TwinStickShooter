#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 pos) : Monobehaviour(pos, "../bin/textures/car.png", 1, 1, glm::vec2{ 30,30 })
{
	radius = getSizeX();
	//EnemyTexture = new aie::Texture("../bin/textures/Enemy.png");
}
float Obstacle::getRadius() { return radius; }