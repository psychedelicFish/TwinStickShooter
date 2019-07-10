#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Player.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

Enemy::Enemy() : Monobehaviour("../bin/textures/Insect.png", 512, 64)
{
	position = { 500, 500 };
	velocity = 200.0f;
	//EnemyTexture = new aie::Texture("../bin/textures/Enemy.png");
}

void Enemy::draw(aie::Renderer2D* renderer)
{
	
	renderer->setUVRect(animationFrame/8.f, 0, 1/8.f, 1);
	renderer->drawSprite(texture, position.x, position.y, sizeX, sizeY, rotationAngle - glm::radians(90.f));
	renderer->setUVRect(0, 0, 1, 1);
	
}
void Enemy::update(float deltaTime, glm::vec2 PlayerPosition){
	
	float rotation = rotationAngle - glm::radians(90.f); // rotation angle - sprite offset 
	position.y += sin(velocity * rotation);
	position.x += cos(velocity * rotation);
	
	glm::vec2 enemyRotationVector = PlayerPosition - position;
	enemyRotationVector = glm::normalize(enemyRotationVector);
	rotationAngle = acos(enemyRotationVector.x);

	if (enemyRotationVector.y < 0) {
		rotationAngle = (glm::radians(360.0f) - rotationAngle);
	}
	
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