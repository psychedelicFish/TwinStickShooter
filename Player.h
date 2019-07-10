#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
class Enemy;
class Weapon;
class Player : public Monobehaviour
{
	aie::Renderer2D* m_2dRenderer;
	glm::vec2 velocity;
	glm::vec2 mousePosition;
	float speed;
	int rotation;
	//aie::Texture* playerTexture;
	aie::Texture* lightOverlay;
	
	
public:
	Player(Enemy* enemy);
	~Player();
	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;
	//bool collision(Monobehaviour& other) override;
	glm::vec2 spriteSize;
	Weapon* weapon = nullptr;
	Enemy* m_enemy = nullptr;
};
