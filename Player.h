#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
#include <list>
class Enemy;
class Weapon;
class Obstacle;
class Player : public Monobehaviour
{
	aie::Renderer2D* m_2dRenderer;
	glm::vec2 velocity;
	glm::vec2 mousePosition;
	float speed;
	float rotation;
	int health;
	//aie::Texture* playerTexture;
	aie::Texture* lightOverlay;
	
	
	
public:
	Player();
	~Player();
	void Update(float deltaTime,std::list<std::shared_ptr<Enemy>>& e, std::list<std::shared_ptr<Obstacle>>& o);
	void draw(aie::Renderer2D* renderer);
	void TakeDamage(int dmg);
	//bool collision(Monobehaviour& other) override;
	glm::vec2 spriteSize;
	Weapon* weapon = nullptr;
	bool Alive;
	//std::list<std::shared_ptr<Monobehaviour>> m_enemy;
};
