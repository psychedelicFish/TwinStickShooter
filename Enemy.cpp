#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>





using ObstacleList = std::list<std::shared_ptr<Obstacle>>;
Enemy::Enemy(glm::vec2 pos) : Monobehaviour(pos,"../bin/textures/Insect.png", 8, 1, glm::vec2{ 30,30 })
{
	velocity = 50.0f;
	Active = false;
	//EnemyTexture = new aie::Texture("../bin/textures/Enemy.png");
}

void Enemy::setPosition(float x, float y) {
	
	position.x = x;
	position.y = y;
}
void Enemy::draw(aie::Renderer2D* renderer)
{
	float x = (animationFrame % (int)frameX) / frameX;
	float y = (animationFrame / (int)frameX) / frameY;
	renderer->setUVRect(x, y, 1/frameX, 1/frameY);
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY, rotationAngle - glm::radians(90.f));
	renderer->setUVRect(0, 0, 1, 1);
	//renderer->drawLine(position.x, position.y, ahead.x, ahead.y);
	//renderer->drawLine(position.x, position.y, avoidance.x, avoidance.y);
	
}
void Enemy::update(float deltaTime, glm::vec2 PlayerPosition, const ObstacleList& obstacleList) {


	glm::vec2 enemyRotationVector = PlayerPosition - position; // Create a vector to player position

	enemyRotationVector = glm::normalize(enemyRotationVector);

	rotationAngle = acos(enemyRotationVector.x); //create rotation angle

	if (enemyRotationVector.y < 0) {
		rotationAngle = (glm::radians(360.0f) - rotationAngle);
	}

	position.y += sin(rotationAngle) * velocity * deltaTime;
	position.x += cos(rotationAngle) * velocity * deltaTime;

	for (auto it : obstacleList) {
		if (collision(it)) {
			position.y -= sin(rotationAngle) * velocity * deltaTime;
			position.x -= cos(rotationAngle) * velocity * deltaTime;
			handleCollisionObstacle(it, deltaTime);
		}
	}
	timer += deltaTime;

	if (timer > animationTime) {
		animationFrame++;
		timer = 0;
	}
	if (animationFrame > frameX) {
		animationFrame = 0;
	}

}

void Enemy::handleCollisionObstacle(const std::shared_ptr<Obstacle> obstacle, float deltaTime) {
	if (position.x < obstacle->getX() + obstacle->getSizeX()) {
		position.x = position.x + sin(rotationAngle)*  velocity * deltaTime;
	}
	if (position.x > obstacle->getX() - obstacle->getSizeX()) {
		position.x = position.x + sin(rotationAngle)*  velocity * deltaTime;
	}
	if (position.y < obstacle->getY() + obstacle->getSizeY()) {
		position.y = position.y + cos(rotationAngle) * velocity * deltaTime;
	}
	if (position.y > obstacle->getY() - obstacle->getSizeY()) {
		position.y = position.y + cos(rotationAngle) * velocity * deltaTime;
	}
}

void Enemy::Attack(std::shared_ptr<Player> player) {
	player->TakeDamage(10);
}
