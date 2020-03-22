#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Node.h"
#include "Map.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>

Enemy::Enemy(glm::vec2 pos, std::shared_ptr<aie::Texture> texture) : Monobehaviour(pos, 8, 1, glm::vec2{ 30,30 })
{
	speed = 50.0f; //speed of enemy
	Active = false; //set the enemy to inactive
	Texture = texture; //set the pointer to the correct texture
	attackTime = .5f; //intialise how often the enemy attacks
	attackTimer = 1.f; //intialise the attack timer to something high so it attacks the player on first contact
	current_velocity = { 0,0 };
	state = PATHING;
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
	renderer->drawSprite(Texture.get(), position.x, position.y, sizeX, sizeY, rotationAngle - glm::radians(90.f));
}
void Enemy::update(float deltaTime, Map& map, Player& player) {
	
	if (state == PATHING) {
		pathTimer += deltaTime;
		if (pathTimer >= 1.f) {
			QueryPath(map, player.getPosition());
			pathTimer = 0.0f;
		}


		DirectionToNode();
		DirectionToPlayer(player.getPosition());
		CalculateRotation();
		CalculateVelocity(deltaTime);
		Walk(deltaTime);
	}
	if (state == ATTACKING) {
		Attack(player, deltaTime);
	}
	
	if (CheckDistanceFromPlayer(player.getPosition()) == true) {
		state = ATTACKING;
	}
	else {
		state = PATHING;
	}

	timer += deltaTime;
	AdjustAnimationFrame();
}

bool Enemy::CheckDistanceFromPlayer(glm::vec2 playerPosition) {
	float distance = glm::distance(playerPosition, position);
	if (distance < 30.f) {
		return true;
	}
	else {
		return false;
	}
}

void Enemy::Attack(Player& player, float deltaTime) {
	attackTimer += deltaTime; // increase the attack timer 
	if (attackTimer > attackTime) { //if the attack timer is greater then the attack rate 
		player.TakeDamage(10); //damage the player 
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