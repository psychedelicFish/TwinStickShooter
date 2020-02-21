#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
#include <list>
class Player;
class Obstacle;
using ObstacleList = std::list<std::shared_ptr<Obstacle>>;
class Enemy : public Monobehaviour
{
protected:
	aie::Texture* EnemyTexture; //Enemies Texture
	
								//Animation stuff
	float timer = 0.0f; 
	int animationFrame = 0;
	float animationTime = 0.055f;

	//Angle of rotation
	float rotationAngle = 0.f;

	float speed;//speed at which the enemy moves
	glm::vec2 desired_velocity;
	glm::vec2 current_velocity;
	glm::vec2 directionToPlayer;
	float attackTime; //How long till the enemy attacks
	float attackTimer; //Timer based off of deltaTime
	
public:
	Enemy(glm::vec2 pos, aie::Texture* texture); //constructer
	
	bool Active; //Is the enemy active in the scene
	//~Enemy();
	
	void update(float deltaTime, glm::vec2 PlayerPosition, const ObstacleList& obstacleList); 
	void draw(aie::Renderer2D* renderer) override;
	
	void handleCollisionObstacle(const std::shared_ptr<Obstacle> obstacle, float deltaTime); //Handles collision logic
	
	void setPosition(float x, float y); //sets the position of the enemy when released from pooler
	void Attack(std::shared_ptr<Player> player, float deltaTime); //Allows the enemy to attack

	void DirectionToPlayer(glm::vec2 PlayerPosition);
	void Walk(float deltaTime);
	void CalculateRotation();
	void CalculateVelocity(float deltaTime);


	void AdjustAnimationFrame();
};
