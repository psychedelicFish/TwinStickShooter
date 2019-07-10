#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
class Player;
class Enemy : public Monobehaviour
{
protected:
	aie::Texture* EnemyTexture;
	float timer = 0.0f;
	int animationFrame = 0;
	float animationTime = 0.055f;

	float rotationAngle = 0.f;
	glm::vec2 playerPosition;
	glm::vec2 rotationVec;
	float velocity;
	float responseTime = 0.055f;
	float responseTimer = 0.0f;
	
public:
	Enemy();
	~Enemy();
	void update(float deltaTime, glm::vec2 PlayerPosition);
	void draw(aie::Renderer2D* renderer) override;
};
