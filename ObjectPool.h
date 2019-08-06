#pragma once
#include <list>
#include <iostream>
#include "Enemy.h"
#include "Bullet.h"

class EnemyObjectPool {

protected:
	std::list<std::shared_ptr<Enemy>> pool;
public:
	EnemyObjectPool (int amountToPool) {
		for (int i = 0; i < amountToPool; i++) {
			std::shared_ptr<Enemy> enemy(new Enemy({ 1000, 1000 }));
			enemy->Active = false;
			pool.push_back(enemy);
			std::cout << pool.size();
		}
	}
	std::shared_ptr<Enemy> GetObjectFromPool() {
		for (std::shared_ptr<Enemy> object : pool) {
			if (!object->Active) {
				object->Active = true;
				return object;
			}
		}
		return nullptr;
	}

};

class BulletObjectPool {
protected:
	std::list<std::shared_ptr<Bullet>> pool;
public:	
	BulletObjectPool(int amountToPool) {
		for (int i = 0; i < amountToPool; i++) {
			std::shared_ptr<Bullet> bullet(new Bullet(0, { 1000,1000 }, 0, 0));
			bullet->Active = false;
			pool.push_back(bullet);
		}
	}
	std::shared_ptr<Bullet> GetObjectFromPool() {
		for (std::shared_ptr<Bullet> object : pool) {
			if (!object->Active) {
				object->Active = true;
				return object;
			}
			else {
				std::shared_ptr<Bullet> bullet(new Bullet(0, { 1000,1000 }, 0, 0));
				bullet->Active = true;
				pool.push_back(bullet);
				return bullet;
			}
		}
		return nullptr;
	}
		
};

