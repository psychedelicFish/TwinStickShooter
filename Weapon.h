#pragma once
#include <list>
#include "Monobehaviour.h"
class Bullet;
class Weapon
{
protected:

	float fireRate;
	glm::vec2 pos;
	float Rotation;

public:
	Weapon(float x, float y, float rotation);
	std::list<Bullet*> bulletList;
	void Fire(float deltaTime);
	void update(float deltaTime, float x, float y, float rotation);
	float GetFireRate();
};