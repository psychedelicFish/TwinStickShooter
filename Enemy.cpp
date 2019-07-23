#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>




using ObstacleList = std::list<std::shared_ptr<Obstacle>>;
Enemy::Enemy(glm::vec2 pos) : Monobehaviour(pos,"../bin/textures/Insect.png", 8, 1, glm::vec2{ 30,30 })
{
	velocity = 50.0f;
	//EnemyTexture = new aie::Texture("../bin/textures/Enemy.png");
}

void Enemy::draw(aie::Renderer2D* renderer)
{
	float x = (animationFrame % (int)frameX) / frameX;
	float y = (animationFrame / (int)frameX) / frameY;
	renderer->setUVRect(x, y, 1/frameX, 1/frameY);
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY, rotationAngle - glm::radians(90.f));
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawLine(position.x, position.y, ahead.x, ahead.y);
	
}
void Enemy::update(float deltaTime, glm::vec2 PlayerPosition, const ObstacleList& obstacleList){
	
	float desiredAngle = 0.0f;
	glm::vec2 enemyRotationVector = PlayerPosition - position; // Create a vector to player position
	enemyRotationVector = glm::normalize(enemyRotationVector); // normalise
	desiredAngle = acos(enemyRotationVector.x); //create rotation angle

	if (enemyRotationVector.y < 0) {
		desiredAngle = (glm::radians(360.0f) - desiredAngle);
	}

	glm::vec2 avoidance = collisionAvoidance(obstacleList);
	if (avoidance.x != 0 || avoidance.y != 0) {
		desiredAngle += glm::radians(45.f);
	}
	
	position.y += sin(desiredAngle) * velocity * deltaTime;
	position.x += cos(desiredAngle) * velocity * deltaTime;

	rotationAngle = acos(enemyRotationVector.x);
	if (rotationAngle != desiredAngle) {};
	
	ahead = { position.x + cos(rotationAngle) * 25, position.y + sin(rotationAngle) * 25 };
	ahead2 = { (position.x + cos(rotationAngle) * 25) * 0.5, (position.y + sin(rotationAngle) * 25) * 0.5 };
	
	//position.x += avoidance.x * deltaTime;
	//position.y += avoidance.y * deltaTime;

	timer += deltaTime;
	if (timer > animationTime) {
		animationFrame = animationFrame + 1;
		timer = 0;
	}
	if (animationFrame > 8) {
		animationFrame = 0; 
	}

	std::cout << position.x << " " << position.y << std::endl;
}


glm::vec2 Enemy::collisionAvoidance(const ObstacleList& obstacleList){
	auto mostThreatning = mostThreatening(obstacleList);
	glm::vec2 avoidanceVec = { 0,0 };

	if (mostThreatning) {
		avoidanceVec = { ahead.x - mostThreatning->getX(), ahead.y - mostThreatning->getY() };
		glm::normalize(avoidanceVec);
		avoidanceVec = { avoidanceVec.x * mostThreatning->getSizeX() * 2, avoidanceVec.y};
	}
	return avoidanceVec;
}

std::shared_ptr<Obstacle> Enemy:: mostThreatening(const ObstacleList& obstacleList){
	std::shared_ptr<Obstacle> mostThreat = nullptr;

	for (auto it : obstacleList)
	{
		bool collision = willCollide(ahead, ahead2, it);
		if (collision && (mostThreat == nullptr || glm::distance(position, it->getPosition()) < 
			glm::distance(position, mostThreat->getPosition())))
		{
			mostThreat = it;
		}
	}
	return mostThreat;
}

bool Enemy::willCollide(glm::vec2 ahead, glm::vec2 ahead2, std::shared_ptr<Obstacle> obstacle){
	return glm::distance(obstacle->getPosition(), ahead) <= obstacle->getRadius() ||
		glm::distance(obstacle->getPosition(), ahead2) <= obstacle->getRadius();
}
