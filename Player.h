#pragma once
#include "Monobehaviour.h"
#include <Texture.h>

class Weapon;
class Player : Monobehaviour
{
	aie::Renderer2D* m_2dRenderer;
	glm::vec2 velocity;
	glm::vec2 mousePosition;
	float speed;
	int rotation;
	float timer;
	aie::Texture* playerTexture;
	
	
public:
	Player();
	~Player();
	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;
	bool collision(Monobehaviour& other) override;
	glm::vec2 spriteSize;
	Weapon* weapon = nullptr;
};
