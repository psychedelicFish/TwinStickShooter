#pragma once
#include <list>
#include "Monobehaviour.h"
#include "ObjectPool.h"
class Bullet;
class Weapon
{
protected:
	
	float fireRate; //how fast the weapon can fire bullets
	glm::vec2 pos; //where it is relative to the player
	float Rotation; //which way the bullets will fire

public:
	Weapon(float x, float y, float rotation); //constructer
	std::shared_ptr<Bullet> Fire(float deltaTime, std::shared_ptr<BulletObjectPool> bulletPool); //shoots the bullets
	void update(float deltaTime, float x, float y, float rotation);
	float GetFireRate(); //returns the firerate of the weapon
};