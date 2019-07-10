#define _USE_MATH_DEFINES
#include "Weapon.h"
#include "Bullet.h"
#include <math.h>


Weapon::Weapon(float x, float y, float rotation)
{
	fireRate = .125f;
	pos.x = x;
	pos.y = y;
	Rotation = ((rotation* M_PI) / 180);
}

std::shared_ptr<Bullet> Weapon::Fire(float deltaTime)
{
	std::shared_ptr<Bullet> bullet (new Bullet(10, pos.x, pos.y, Rotation, 3.f));
	return bullet;
}
void Weapon::update(float deltaTime, float x, float y, float rotation)
{
	Rotation = ((rotation* M_PI) / 180);
	pos.x = x + cos(Rotation) * 23;
	pos.y = y + sin(Rotation) * 23;
	//for (Bullet* bullet : bulletList)
	//{
		//bullet->update(deltaTime);
	//}
}
float Weapon::GetFireRate()
{
	return fireRate;
}
