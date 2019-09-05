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
Enemy::Enemy(glm::vec2 pos, aie::Texture* Texture) : Monobehaviour(pos, 8, 1, glm::vec2{ 30,30 })
{
	velocity = 50.0f; //speed of enemy
	Active = false; //set the enemy to inactive
	texture = Texture; //set the pointer to the correct texture
	attackTime = .5f; //intialise how oftern the enemy attacks
	attackTimer = 1.f; //intialise the attack timer to something high so it attacks the player on first contace
}

void Enemy::setPosition(float x, float y) { //sets the enemies position
	
	position.x = x;
	position.y = y;
}
void Enemy::draw(aie::Renderer2D* renderer)
{
	float x = (animationFrame % (int)frameX) / frameX;
	float y = (animationFrame / (int)frameX) / frameY;
	renderer->setUVRect(x, y, 1/frameX, 1/frameY);
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY, rotationAngle - glm::radians(90.f));
}
void Enemy::update(float deltaTime, glm::vec2 PlayerPosition, const ObstacleList& obstacleList) {


	glm::vec2 enemyRotationVector = PlayerPosition - position; // Create a vector to player position

	enemyRotationVector = glm::normalize(enemyRotationVector); //normalise the vector

	rotationAngle = acos(enemyRotationVector.x); //create rotation angle

	if (enemyRotationVector.y < 0) {
		rotationAngle = (glm::radians(360.0f) - rotationAngle); //if we are -y we need to adjust the radians value
	}

	position.y += sin(rotationAngle) * velocity * deltaTime; //set the new position base on angle and velocity 
	position.x += cos(rotationAngle) * velocity * deltaTime; // for both the x and the y

	for (auto it : obstacleList) { //Iterate through the obstacle list
		if (collision(it)) {
			position.y -= sin(rotationAngle) * velocity * deltaTime; //bounce back off the object in the oppisite direction
			position.x -= cos(rotationAngle) * velocity * deltaTime;
			handleCollisionObstacle(it, deltaTime);
		}
	}
	timer += deltaTime;

	if (timer > animationTime) { //adjust the animation frames of the enemy
		animationFrame++;
		timer = 0;
	}
	if (animationFrame > frameX) {
		animationFrame = 0;
	}

}
//This function will slide the enemy around the obstacle based on its position to the obstacle
//This avoids the issue of getting stuck on the obstacle
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

void Enemy::Attack(std::shared_ptr<Player> player, float deltaTime) {
	attackTimer += deltaTime; // increase the attack timer 
	if (attackTimer > attackTime) { //if the attack timer is greater then the attack rate 
		player->TakeDamage(10); //damage the player 
		attackTimer = 0.0f; // reset the timer
	}
	
}
