#include "TwinStickShooterApp.h"
#include "HealthBar.h"
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
}

TwinStickShooterApp::~TwinStickShooterApp() {

}	

bool TwinStickShooterApp::startup() {
	
	GameState = &TwinStickShooterApp::MainMenu;
	srand(((unsigned int)(time(nullptr))));
	m_2dRenderer = new aie::Renderer2D();
	newgame.reset(new Button("New Game", 720.f/2, 720.0f*.5, 120.f, 50.f));
	ExitGame.reset(new Button("Exit Game", 720.f / 2, 720.f *.5 - 100, 120.f, 50.f));
	
	fontControls = new aie::Font("./bin/fonts/consolas.ttf", 24);
	titleFont = new aie::Font("./bin/fonts/consolas_bold.ttf", 60);
	menuLight = new aie::Texture("./bin/textures/MenuLight.png");
	menuGreen = new aie::Texture("./bin/textures/MenuGreen.png");
	No.reset(new Button("No", BoxPosX / 1.5f, BoxPosY - 2.5*50.f, 120.f, 50.f));
	Yes.reset(new Button("Yes", BoxPosX*1.25, BoxPosY - 2.5*50.f, 120.f, 50.f));

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
	assert(GameState != nullptr);
	(this->*GameState)(deltaTime);
}

void TwinStickShooterApp::draw() {
	
	// wipe the screen to the background colour
	clearScreen();
	// begin drawing sprites
	m_2dRenderer->begin();
	
	if (GameState == &TwinStickShooterApp::MainMenu) { //Check the state of the game is the main menu
		m_2dRenderer->setCameraPos(0, 0);
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
		m_2dRenderer->setCameraPos(0, 0);
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
		m_2dRenderer->setUVRect(0, 0, 1, 1);
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
		m_2dRenderer->setUVRect(0, 0, 1, 1);
		player->draw(m_2dRenderer);
		bar->draw(m_2dRenderer, 600, 700);
		snprintf(scoreText, 64, "Your Score : %i points", score);
		m_2dRenderer->drawText(fontControls, scoreText, 0, 690);
	}
	else if (GameState == &TwinStickShooterApp::GameOver) {

		m_2dRenderer->setCameraPos(0, 0);
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
		snprintf(finalScoreText, 64, "You only score : %i points", score);
		m_2dRenderer->drawText(fontControls, finalScoreText, centredPosX, centredPosY - textHeight * 3);
		m_2dRenderer->drawText(fontControls, "Would you like to run?", centredPosX, centredPosY - textHeight * 4);
		
		No->Draw(m_2dRenderer);
		Yes->Draw(m_2dRenderer);

		m_2dRenderer->setUVRect(0, 0, 1, 1);
		m_2dRenderer->drawSprite(menuLight, menuLightPosX, menuLightPosY, 0, 0);
	}
	m_2dRenderer->end();
}
void TwinStickShooterApp::MainMenu(float deltaTime) {
	
	m_2dRenderer->setCameraPos(0, 0);
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	if (newgame->Update()) {
		Continue.reset(new Button("Continue", BoxPosX, BoxPosY - 2.5*50.f, 120.f, 50.f));
		GameState = &TwinStickShooterApp::StartGame;
		}
	if (ExitGame->Update()) {
		GameState = &TwinStickShooterApp::Exit;
	}
	
}

#pragma region PlayGame
void TwinStickShooterApp::PlayGame(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();	
	gameTimer += deltaTime;
	
	//Making sure there are always the correct amount of enemies in the scene
	//Will always populate the scene up to the max Enemies amount
	assert(maxEnemies > 0);
	if (enemiesInScene < maxEnemies) {
		for (int i = 0; i < maxEnemies - enemiesInScene; i++) {
			std::shared_ptr<Enemy> enemy = enemyPool->GetObjectFromPool();

			while (true) {
				int x = rand() % 721;
				int y = rand() % 721;
				if (abs(player->getX() - x) < 30 &&
				   (abs(player->getY() - y) < 30)) {
					continue;
				}

				enemy->setPosition(x, y);
				enemyList.push_back(enemy);
				enemiesInScene++;
				break;
			}
		}
	}
	//Checking to see if we are firing 
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		timer += deltaTime;
		if (timer > m_weapon->GetFireRate())
		{
			std::shared_ptr<Bullet> bullet(m_weapon->Fire(deltaTime, bulletPool)); //grabbing a bullet from the pool
			bulletList.push_back(bullet); //adding it to the list
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
				(*bullet)->Active = false;
				auto bulletcopy = bullet; // make a copy of the bullet
				bullet++;// increase iterator
				bulletList.erase(bulletcopy);

				if (bullet == bulletList.end()) { // make sure that we havent increased beyond the last
					break; // if we have break the loop.
				}
			}
			(*bullet)->update(deltaTime);// updates the bullet
			
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
					(*enemy)->setPosition(10000, 10000);
					(*enemy)->Active = false;
					
					enemiesInScene--;
					maxEnemies++;
					enemy++;
					score += 1 * gameTimer;
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
	
	player->Update(deltaTime, enemyList, obstacleList, x, y);

	for (std::shared_ptr<Enemy> enemy : enemyList) {
		enemy->update(deltaTime, *map, obstacleList, player->getPosition());
		//std::cout << enemy->getX() << " , " << enemy->getY() << std::endl;
		if (enemy->collision(player)) {
			enemy->Attack(player, deltaTime);
			//std::cout << player->getCurrentHealth() << std::endl;
			bar->UpdateHealth(player->getCurrentHealth());
			if (!player->Alive) {
				GameState = &TwinStickShooterApp::GameOver;
			}
		}
	}

	map->update(deltaTime, player->getPosition());

	for (auto e = enemyList.begin(); e != enemyList.end(); e++) {
		if ((*e)->getX() > player->getX() + 720 / 2 || (*e)->getX() < player->getX() - 720 / 2 ||
			(*e)->getY() > player->getY() + 720 / 2 || (*e)->getY() < player->getY() - 720 / 2) {

			(*e)->Active = false;
			auto ecopy = e;
			e++;
			enemyList.erase(ecopy);
			enemiesInScene--;

			if (e == enemyList.end()) {
				break;
			}
		}
	}

}
#pragma endregion

void TwinStickShooterApp::StartGame(float deltaTime){
	
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	
	if (CreatedAssets == false) {
		
		maxEnemies = 1; //intialise max number of enemies in the scene
		enemiesInScene = 0; //intialise current enemies in scene 
		bulletsPooled = 100; //intialise amount of bullets pooled
		obstaclesPooled = 10;//intialise amount of obstacles pooled 
		obstaclesInScene = 0; //intialise current obstacles in scene
		score = 0;
		gameTimer = 0.f;
		
		//Create the player
		player.reset(new Player());
		
		//Create the map
		map.reset(new Map());
		
		//Set the weapon to the created players weapon
		m_weapon = player->weapon;
		
		//Create the object pools
		enemyPool.reset(new EnemyObjectPool(maxEnemies * 100)); //100 is so we pool enough enemies to use before we create new ones
		bulletPool.reset(new BulletObjectPool(bulletsPooled));
		obstaclePool.reset(new ObstaclePool(obstaclesPooled));

		bar.reset(new HealthBar(player->GetMaxHealth(), 600, 600, 200, 20));
		
		CreatedAssets = true; //Set this to true so it cant keep doing it over and over
	}
	if (Continue->Update()) { //check if the continue button is pressed
		GameState = &TwinStickShooterApp::PlayGame; //set the state machine to point at the play game function
	}
}

void TwinStickShooterApp::GameOver(float deltaTime) {
	
	aie::Input* input = aie::Input::getInstance();
	menuLightPosX = input->getMouseX();
	menuLightPosY = input->getMouseY();
	for (auto enemy = enemyList.begin(); enemy != enemyList.end(); enemy++) {
		auto enemycopy = enemy;
		(*enemy)->setPosition(10000, 10000);
		(*enemy)->Active = false;

		enemiesInScene--;
		enemy++;
		enemyList.erase(enemycopy);
		if (enemy == enemyList.end())
		{
			break;
		}

	}
	
	if (Yes->Update()) {
		GameState = &TwinStickShooterApp::Exit;
	}
	if (No->Update()) {
		CreatedAssets = false;
		GameState = &TwinStickShooterApp::MainMenu;
	}
}
void TwinStickShooterApp::Exit(float deltaTime) {
	m_gameOver = true;
}
