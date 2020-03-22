#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
#include <list>

class Enemy;
class Weapon;
class Map;
class Player : public Monobehaviour
{
	aie::Renderer2D* m_2dRenderer;
	glm::vec2 velocity; // vector for moving the player 
	glm::vec2 mousePosition; //where the mouse is in world space
	float speed; //how fast the player can move per frame
	float rotation; //which way the player is facing in radians
	//Health stuff
	int currentHealth;
	int MaxHealth;
	std::shared_ptr<aie::Texture> lightOverlay; //this is the overlay for the player
	
	//Camera Position relative to the player
	float cameraX;
	float cameraY;
	
	
public:
	Player(); //constructer
	~Player();//destructer
	void Update(float deltaTime, Map& map);
	void draw(aie::Renderer2D* renderer);
	void TakeDamage(int dmg); //allows the player to take damage
	glm::vec2 spriteSize; //how big the player sprite is 
	std::shared_ptr<Weapon> weapon = nullptr; //pointer to the players weapon - used for getting the bullets in the right position
	bool Alive; //is the player alive or not
	//Returns the health values
	int GetMaxHealth();
	int getCurrentHealth();

};
