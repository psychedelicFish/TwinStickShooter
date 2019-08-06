#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Map.h"
#include <list>
#include "ObjectPool.h"

class Player;
class Enemy;
class Bullet;
class Weapon;
class Obstacle;
class Menu;
class Button;
class TwinStickShooterApp : public aie::Application {
public:
	
	TwinStickShooterApp();
	virtual ~TwinStickShooterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	//State Machine
	using gameState = void(TwinStickShooterApp::*)(float deltaTime);
	
	gameState GameState;

	void MainMenu(float deltaTime);
	void StartGame(float deltaTime);
	void PlayGame(float deltaTime);
	void Options(float deltaTime);
	void Exit(float deltaTime);
	void GameOver(float deltaTime);

protected:
	std::shared_ptr<EnemyObjectPool> enemyPool;
	std::shared_ptr<BulletObjectPool> bulletPool;
	int enemiesInScene;
	int maxEnemies;
	//aie::Texture* playerTexture;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font* fontControls;
	aie::Font* titleFont;
	std::shared_ptr <Player> player;
	bool CreatedAssets = false;
	Weapon* m_weapon;
	Menu* menu;
	
	std::list<std::shared_ptr<Bullet>> bulletList;
	std::list < std::shared_ptr<Obstacle> >obstacleList;
	std::list<std::shared_ptr<Enemy>> enemyList;
	//Menu Stuff
	std::shared_ptr<Button> newgame;
	std::shared_ptr<Button> Continue;
	std::shared_ptr<Button> Yes;
	std::shared_ptr<Button> No;
	std::shared_ptr<Button> ExitGame;
	float BoxSizeX = 400;
	float BoxSizeY = 300;
	float BoxPosX = 720/2;
	float BoxPosY = 720/2;
	float menuLightPosX;
	float menuLightPosY;
	Map* map;
	aie::Texture* Texture;
	aie::Texture* menuLight;
	aie::Texture* menuGreen;
	float timer = 10.0f;


};