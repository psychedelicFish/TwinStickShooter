#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Map.h"
#include <list>
#include "ObjectPool.h"

class HealthBar;
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
	void Exit(float deltaTime);
	void GameOver(float deltaTime);

protected:
	aie::Renderer2D*	m_2dRenderer;
	
	//Object Poolers
	std::shared_ptr<EnemyObjectPool> enemyPool;
	std::shared_ptr<BulletObjectPool> bulletPool;
	
	//Variables for poolers and asset creation
	int enemiesInScene;
	int maxEnemies;
	int obstaclesPooled;
	int obstaclesInScene;
	int bulletsPooled;
	bool CreatedAssets = false;
	
	//Basic Assest Containers
	std::shared_ptr<Map> map;
	Player* player;
	std::shared_ptr <Weapon> m_weapon;
	std::list<std::shared_ptr<Bullet>> bulletList;
	std::list <std::shared_ptr<Obstacle>> obstacleList;
	std::list<std::shared_ptr<Enemy>> enemyList;
	
	//Menu Stuff
	std::shared_ptr<Button> newgame;
	std::shared_ptr<Button> Continue;
	std::shared_ptr<Button> Yes;
	std::shared_ptr<Button> No;
	std::shared_ptr<Button> ExitGame;
	aie::Texture* menuLight = nullptr;
	aie::Texture* menuGreen = nullptr;
	aie::Font* fontControls;
	aie::Font* titleFont;
	float BoxSizeX = 400;
	float BoxSizeY = 300;
	float BoxPosX = 720/2;
	float BoxPosY = 720/2;
	float menuLightPosX;
	float menuLightPosY;

	float timer = 10.0f;
	
	//UI stuff 
	float gameTimer;
	char scoreText[64];
	char finalScoreText[64];
	int score;
	std::shared_ptr<HealthBar> bar;
};