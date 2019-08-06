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
	aie::Texture* EnemyTexture;
	float timer = 0.0f;
	int animationFrame = 0;
	float animationTime = 0.055f;

	float rotationAngle = 0.f;

	glm::vec2 rotationVec;

	glm::vec2 ahead;
	glm::vec2 ahead2;
	glm::vec2 avoidance = { 0,0 };

	float velocity;
	float responseTime = 0.055f;
	float responseTimer = 0.0f;
	
public:
	Enemy(glm::vec2 pos);
	bool Active;
	//~Enemy();
	void update(float deltaTime, glm::vec2 PlayerPosition, const ObstacleList& obstacleList);
	void draw(aie::Renderer2D* renderer) override;
	void handleCollisionObstacle(const std::shared_ptr<Obstacle> obstacle, float deltaTime);
	void setPosition(float x, float y);
	void Attack(std::shared_ptr<Player> player);
};
