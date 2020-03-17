#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "Pathfinding.h"
#include "Map.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>

using ObstacleList = std::list<std::shared_ptr<Obstacle>>;
Enemy::Enemy(glm::vec2 pos, aie::Texture* Texture) : Monobehaviour(pos, 8, 1, glm::vec2{ 30,30 })
{
	speed = 50.0f; //speed of enemy
	Active = false; //set the enemy to inactive
	texture = Texture; //set the pointer to the correct texture
	attackTime = .5f; //intialise how often the enemy attacks
	attackTimer = 1.f; //intialise the attack timer to something high so it attacks the player on first contact
	current_velocity = { 0,0 };
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
	for (Node* n : path) {
		n->Draw(renderer);
	}
}
void Enemy::update(float deltaTime, Map& map, const ObstacleList& obstacleList, glm::vec2 playerPosition) {
	
	pathTimer += deltaTime;
	if (pathTimer >= .25f) {
		QueryPath(map, playerPosition);
		pathTimer = 0.0f;
	}
	DirectionToNode();
	DirectionToPlayer(playerPosition);
	CalculateRotation();
	CalculateVelocity(deltaTime);
	Walk(deltaTime);

	for (auto it : obstacleList) { //Iterate through the obstacle list
		if (collision(it)) {
			position.y -= sin(rotationAngle) * speed * deltaTime; //bounce back off the object in the oppisite direction
			position.x -= cos(rotationAngle) * speed * deltaTime;
			handleCollisionObstacle(it, deltaTime);
		}
	}
	timer += deltaTime;
	AdjustAnimationFrame();
}
//This function will slide the enemy around the obstacle based on its position to the obstacle
//This avoids the issue of getting stuck on the obstacle
void Enemy::handleCollisionObstacle(const std::shared_ptr<Obstacle> obstacle, float deltaTime) {
	if (position.x < obstacle->getX() + obstacle->getSizeX()) {
		position.x = position.x + sin(rotationAngle) * speed * deltaTime;
	}
	if (position.x > obstacle->getX() - obstacle->getSizeX()) {
		position.x = position.x + sin(rotationAngle) * speed * deltaTime;
	}
	if (position.y < obstacle->getY() + obstacle->getSizeY()) {
		position.y = position.y + cos(rotationAngle) * speed * deltaTime;
	}
	if (position.y > obstacle->getY() - obstacle->getSizeY()) {
		position.y = position.y + cos(rotationAngle) * speed * deltaTime;
	}
}

void Enemy::Attack(std::shared_ptr<Player> player, float deltaTime) {
	attackTimer += deltaTime; // increase the attack timer 
	if (attackTimer > attackTime) { //if the attack timer is greater then the attack rate 
		player->TakeDamage(10); //damage the player 
		attackTimer = 0.0f; // reset the timer
	}
}

void Enemy::Walk(float deltaTime) {
	position += current_velocity * deltaTime; //set the new position based on angle and velocity 
	
	if (path.empty()) {
		return;
	}

	if (Arrive()) {
		path.pop_front();
	}
}

bool Enemy::Arrive() {
	return((*path.begin())->GetPosition().x - position.x  < 0.05 && ((*path.begin())->GetPosition().y - position.y < 0.05));
}

void Enemy::CalculateRotation() {
	
	 //normalise the vector

	rotationAngle = acos(directionToPlayer.x); //create rotation angle

	if (directionToPlayer.y < 0) {
		rotationAngle = (glm::radians(360.0f) - rotationAngle); //if we are -y we need to adjust the radians value
	}
}

void Enemy::AdjustAnimationFrame() {

	if (timer > animationTime) { //adjust the animation frames of the enemy
		animationFrame++;
		timer = 0;
	}
	if (animationFrame > frameX) {
		animationFrame = 0;
	}
}

void Enemy::CalculateVelocity(float deltaTime) {
	
	desired_velocity = directionToNode * speed;
	
	glm::vec2 steering = desired_velocity - current_velocity;

	current_velocity = current_velocity + steering * deltaTime;
}	

void Enemy::DirectionToNode() {
	if (path.empty()) {
		return;
	}
	directionToNode = (*path.begin())->GetPosition() - position;
	directionToNode = glm::normalize(directionToNode);
}

void Enemy::QueryPath(Map& map, glm::vec2 playerPosition) 
{
	path = map.QueryPathfinder(position, playerPosition);
}

void Enemy::DirectionToPlayer(glm::vec2 playerPosition) {
	directionToPlayer = playerPosition - position;
	directionToPlayer = glm::normalize(directionToPlayer);
}