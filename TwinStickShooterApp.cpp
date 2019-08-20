#include "TwinStickShooterApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "Weapon.h"
#include "Obstacle.h"
#include "Button.h"
#include <iostream>
#include <string.h>
#include <random>
#include <time.h>



TwinStickShooterApp::TwinStickShooterApp() {
	//playerTexture = new aie::Texture("./textures/car.png");	
}

TwinStickShooterApp::~TwinStickShooterApp() {
	//delete playerTexture;
}

bool TwinStickShooterApp::startup() {
	
	srand(((unsigned int)(time(nullptr))));
	GameState = &TwinStickShooterApp::MainMenu;
	m_2dRenderer = new aie::Renderer2D();
	newgame.reset(new Button("New Game", 720.f/2, 720.0f*.5, 120.f, 50.f));
	ExitGame.reset(new Button("Exit Game", 720.f / 2, 720.f *.5 - 100, 120.f, 50.f));
	fontControls = new aie::Font("./bin/fonts/consolas.ttf", 24);
	titleFont = new aie::Font("./bin/fonts/consolas_bold.ttf", 60);
	menuLight = new aie::Texture("./bin/textures/MenuLight.png");
	menuGreen = new aie::Texture("./bin/textures/MenuGreen.png");
	No.reset(new Button("No", BoxPosX / 1.5f, BoxPosY - 2.5*50.f, 120.f, 50.f));
	Yes.reset(new Button("Yes", BoxPosX*1.25, BoxPosY - 2.5*50.f, 120.f, 50.f));
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	//m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void TwinStickShooterApp::shutdown() {

	///delete m_font;
	delete m_2dRenderer;
	delete fontControls;
	delete titleFont;
	delete menuLight;
	delete menuGreen;
	//delete Texture;
}

void TwinStickShooterApp::update(float deltaTime)
{
	(this->*GameState)(deltaTime);
}

void TwinStickShooterApp::draw() {
	
	//if (GameState == &TwinStickShooterApp::Exit) {
		//r//eturn;
	//}
	// wipe the screen to the background colour
	clearScreen();
	// begin drawing sprites
	m_2dRenderer->begin();
	
	// draw your stuff here!
	
	if (GameState == &TwinStickShooterApp::MainMenu) {
		m_2dRenderer->drawSprite(menuGreen, 720 / 2, 720 / 2);
		float boxx = 720 / 2;
		float boxy = 600;
		float boxSizeX = 100;
		float boxSizeY = 100;
		m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.0f, 0.0f);
		m_2dRenderer->drawBox(boxx, boxy, boxSizeX, boxSizeY);
		float twidth = titleFont->getStringWidth("The Dark");
		float theight = titleFont->getStringHeight("The Dark");
		float centreX = boxx - (twidth * 0.5f) + 2;
		float centreY = boxy - (theight * 0.5f) + 5;
		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		m_2dRenderer->drawText(titleFont, "The Dark", centreX, centreY);
		newgame->Draw(m_2dRenderer);
		ExitGame->Draw(m_2dRenderer);
		m_2dRenderer->setUVRect(0, 0, 1, 1);
		m_2dRenderer->drawSprite(menuLight, menuLightPosX, menuLightPosY, 0, 0);
		
	}
	else if (GameState == &TwinStickShooterApp::StartGame) {
		m_2dRenderer->drawSprite(menuGreen, 720 / 2, 720 / 2);
		m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.0f, 0.0f);
		m_2dRenderer->drawBox(BoxPosX, BoxPosY, BoxSizeX, BoxSizeY);
		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		
		float textWidth = fontControls->getStringWidth("Welcome to the dark");
		float textHeight = fontControls->getStringHeight("Welcome to the dark");
		float centredPosX = BoxPosX - (textWidth * 0.5f) + 2;
		float centredPosY = BoxPosY - (textHeight * 0.5f) + 5;
		
		m_2dRenderer->drawText(fontControls, "Welcome to the dark", centredPosX, centredPosY);
		m_2dRenderer->drawText(fontControls, "WASD to move.", centredPosX, centredPosY - textHeight);
		m_2dRenderer->drawText(fontControls, "Left mouse to shoot.", centredPosX, centredPosY - textHeight * 2);
		m_2dRenderer->drawText(fontControls, "Mouse postion to rotate.", centredPosX, centredPosY - textHeight * 3);
		m_2dRenderer->drawText(fontControls, "Have Fun..... ahaha!", centredPosX, centredPosY - textHeight * 4);
		
		Continue->Draw(m_2dRenderer);
		
		m_2dRenderer->setUVRect(0, 0, 1, 1);
		m_2dRenderer->drawSprite(menuLight, menuLightPosX, menuLightPosY, 0, 0);
	}
	else if (GameState == &TwinStickShooterApp::PlayGame)
	{
		map->draw(m_2dRenderer);
		for (std::shared_ptr<Enemy> enemy : enemyList) {
			enemy->draw(m_2dRenderer);
		}
		for (std::shared_ptr<Obstacle> obstacle : obstacleList) {
			obstacle->draw(m_2dRenderer);
		}
		for (std::shared_ptr<Bullet> bullet : bulletList)
		{
			bullet->draw(m_2dRenderer);
		}
		player->draw(m_2dRenderer);
	}
	else if (GameState == &TwinStickShooterApp::GameOver) {

		
		m_2dRenderer->drawSprite(menuGreen, 720 / 2, 720 / 2);
		m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.0f, 0.0f);
		m_2dRenderer->drawBox(BoxPosX, BoxPosY, BoxSizeX, BoxSizeY);
		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		
		float textWidth = fontControls->getStringWidth("Mwuh ha ha, You have fallen,");
		float textHeight = fontControls->getStringHeight("Mwuh ha ha, You have fallen,");
		float centredPosX = BoxPosX - (textWidth * 0.5f) + 2;
		float centredPosY = BoxPosY - (textHeight * 0.5f) + 5;
		
		m_2dRenderer->drawText(fontControls, "Mwuh ha ha, You have fallen,", centredPosX, centredPosY);
		m_2dRenderer->drawText(fontControls, "to the DARK!!", centredPosX, centredPosY - textHeight);
		m_2dRenderer->drawText(fontControls, "Alone you lay", centredPosX, centredPosY - textHeight * 2);
		m_2dRenderer->drawText(fontControls, "Would you like to run?", centredPosX, centredPosY - textHeight * 3);
		
		No->Draw(m_2dRenderer);
		Yes->Draw(m_2dRenderer);

		m_2dRenderer->setUVRect(0, 0, 1, 1);
		m_2dRenderer->drawSprite(menuLight, menuLightPosX, menuLightPosY, 0, 0);
	}
	m_2dRenderer->end();
}
void TwinStickShooterApp::MainMenu(float deltaTime) {
	
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	if (newgame->Update()) {
		Continue.reset(new Button("Continue", BoxPosX, BoxPosY - 2.5*50.f, 120.f, 50.f));
		GameState = &TwinStickShooterApp::StartGame;
		}
	
}

#pragma region PlayGame
void TwinStickShooterApp::PlayGame(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();
	
	if (enemiesInScene < maxEnemies) {
		for (int i = 0; i < maxEnemies - enemiesInScene; i++) {
			std::shared_ptr<Enemy> enemy = enemyPool->GetObjectFromPool();
			int x = rand() % 720;
			int y = rand() % 720;
			std::cout << i;
			enemy->setPosition(x, y);
			enemyList.push_back(enemy);
			enemiesInScene++;
		}
	}

	// exit the application
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		timer += deltaTime;
		if (timer > m_weapon->GetFireRate())
		{
			std::shared_ptr<Bullet> bullet(m_weapon->Fire(deltaTime, bulletPool));
			bulletList.push_back(bullet);
			//m_weapon->Fire(deltaTime);
			timer = 0.0f;
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (!(bulletList.empty()))
	{
		for (auto bullet = bulletList.begin(); bullet != bulletList.end() || bulletList.empty(); bullet++)
		{
			if ((*bullet)->alive > ((*bullet)->getLife())) {
				std::cout << "Bullet Deleted";
				(*bullet)->Active = false;
				auto bulletcopy = bullet; // make a copy of the bullet
				bullet++;// increase iterator
				bulletList.erase(bulletcopy);
				std::cout << "Called";// erase the bullet that collided from the list 

				if (bullet == bulletList.end()) { // make sure that we havent increased beyond the last
					break; // if we have break the loop.
				}
			}
			(*bullet)->update(deltaTime);// updates the bullet
			
			for (auto obstacle = obstacleList.begin(); obstacle != obstacleList.end(); obstacle++) {

				if ((*bullet)->collision((*obstacle))) {

					(*bullet)->Active = false;
					auto bulletcopy = bullet; // make a copy of the bullet
					bullet++;// increase iterator
					bulletList.erase(bulletcopy);
					std::cout << "Called";// erase the bullet that collided from the list 

					if (bullet == bulletList.end()) { // make sure that we havent increased beyond the last
						break; // if we have break the loop.
					}
				}
				
			}
			if (bullet == bulletList.end()) { // make sure that we havent increased beyond the last

				break; // if we have break the loop.
			}
		}
		for (auto enemy = enemyList.begin(); enemy != enemyList.end(); enemy++) // loops through the enemies
		{
			for (auto bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
			{ //loops through the bullets for each enemies

				if ((*bullet)->collision((*enemy)))
				{ //if a bullet collides with enemy

					auto bulletcopy = bullet; // make a copy of the bullet
					bullet++;// increase iterator
					bulletList.erase(bulletcopy); // erase the bullet that collided from the list 

					auto enemycopy = enemy;
					(*enemy)->Active = false;
					enemiesInScene--;
					enemy++;
					enemyList.erase(enemycopy);
					if (enemy == enemyList.end())
					{
						goto breakEnemyList;
					}
					if (bullet == bulletList.end()) { // make sure that we havent increased beyond the last
						break; // if we have break the loop.
					}
				}
			}
		}
	}
breakEnemyList:
	float x = 0.f;
	float y = 0.f;
	m_2dRenderer->setCameraPos(player->getX() - 720 / 2, player->getY() - 720 / 2);
	m_2dRenderer->getCameraPos(x, y);
	player->Update(deltaTime, enemyList, obstacleList, x, y);

	for (std::shared_ptr<Enemy> enemy : enemyList) {
		enemy->update(deltaTime, player->getPosition(), obstacleList);
		if (enemy->collision(player)) {
			enemy->Attack(player);
			if (!player->Alive) {
				GameState = &TwinStickShooterApp::GameOver;
			}
		}
	}

	
	std::cout << "Camera X: " << x << "Camera Y: " << y << std::endl;
}
#pragma endregion

void TwinStickShooterApp::StartGame(float deltaTime){
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	if (CreatedAssets == false) {
		maxEnemies = 0;
		enemiesInScene = 0;
		//Create the player
		player.reset(new Player());
		//Create the map
		map = new Map();
		//Set the weapon to the created players weapon
		m_weapon = player->weapon;

		//Create the obstacles - Too be changed to the obstacle pooler
		std::shared_ptr<Obstacle> obstacle(new Obstacle({ 300,300 }));
		std::shared_ptr<Obstacle> obstacle1(new Obstacle({ 450, 300 }));
		std::shared_ptr<Obstacle> obstacle2(new Obstacle({ 150, 300 }));
		//Push the created obstacles to a list this will be made obsolete with a pooler
		obstacleList.push_back(obstacle);
		obstacleList.push_back(obstacle1);
		obstacleList.push_back(obstacle2);

		enemyPool.reset(new EnemyObjectPool(maxEnemies));
		bulletPool.reset(new BulletObjectPool(100));
		CreatedAssets = true;
	}
	if (Continue->Update()) {
		GameState = &TwinStickShooterApp::PlayGame;
	}
}

void TwinStickShooterApp::GameOver(float deltaTime) {
	
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	
	if (Yes->Update()) {
		GameState = &TwinStickShooterApp::Exit;
	}
	if (No->Update()) {
		GameState = &TwinStickShooterApp::MainMenu;
	}
}
void TwinStickShooterApp::Exit(float deltaTime) {
	m_gameOver = true;
}
