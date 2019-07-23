#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Map.h"
#include <list>
class Player;
class Enemy;
class Bullet;
class Weapon;
class Obstacle;
class TwinStickShooterApp : public aie::Application {
public:

	TwinStickShooterApp();
	virtual ~TwinStickShooterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	//aie::Texture* playerTexture;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	std::shared_ptr <Player> player;
	
	Weapon* m_weapon;
	
	std::list<std::shared_ptr<Bullet>> bulletList;
	std::list < std::shared_ptr<Obstacle> >obstacleList;
	std::list<std::shared_ptr<Enemy>> enemyList;

	Map* map;
	aie::Texture* Texture;
	float timer = 10.0f;
};