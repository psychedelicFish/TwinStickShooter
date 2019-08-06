#pragma once
#include <list>
#include "Monobehaviour.h"
#include "ObjectPool.h"
class Bullet;
class Weapon
{
protected:
	
	float fireRate;
	glm::vec2 pos;
	float Rotation;

public:
	Weapon(float x, float y, float rotation);
	std::shared_ptr<Bullet> Fire(float deltaTime, std::shared_ptr<BulletObjectPool> bulletPool);
	void update(float deltaTime, float x, float y, float rotation);
	float GetFireRate();
};