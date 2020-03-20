#pragma once
#include <list>
#include <iostream>
#include "Enemy.h"
#include "Bullet.h"
#include <Texture.h>
#include <Renderer2D.h>

//Object Pool classes - This header file handles all the object pooling for Enemies, Obstacles and Bullets 
class EnemyObjectPool {

protected:
	std::list<std::shared_ptr<Enemy>> pool; //the list that holds the pool
	std::shared_ptr<aie::Texture> enemyTexture = textureManager.GetTexture("./bin/textures/Insect.png"); //the texture to pool
public:
	EnemyObjectPool (int amountToPool) { //constructer, takes an int and pools that many objects
		for (int i = 0; i < amountToPool; i++) {
			std::shared_ptr<Enemy> enemy(new Enemy({ 10000, 10000 }, enemyTexture)); //create the enemy
			enemy->Active = false; //sets those objects to be false in the scene
			pool.push_back(enemy); //add the objects to the pool
		}
	}
	std::shared_ptr<Enemy> GetObjectFromPool() { //Function to return the object from the pool
		for (std::shared_ptr<Enemy> object : pool) { //go through eeach object in the pool
			if (!object->Active) { //if we find one that isnt active
				object->Active = true; //set it to active 
				return object; // and return it
			}
			else { //otherwise we need to increase the pool size. This shouldnt happen to often with a decent sized pool
				std::shared_ptr<Enemy> enemy(new Enemy({ 1000,1000}, enemyTexture));
				enemy->Active = true;
				pool.push_back(enemy);
				return enemy;
			}
		}
		return nullptr;
	}

};
//Class for the bullet object pooler - works very simaler to the enemy pooler
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



