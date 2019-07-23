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



TwinStickShooterApp::TwinStickShooterApp() {
	//playerTexture = new aie::Texture("./textures/car.png");
	
	
}

TwinStickShooterApp::~TwinStickShooterApp() {
	//delete playerTexture;
}

bool TwinStickShooterApp::startup() {

	m_2dRenderer = new aie::Renderer2D();

	player.reset(new Player());
	map = new Map();
	m_weapon = player->weapon;
	
	std::shared_ptr<Obstacle> obstacle(new Obstacle({ 300,300 }));
	std::shared_ptr<Obstacle> obstacle1(new Obstacle({450, 300}));
	std::shared_ptr<Obstacle> obstacle2(new Obstacle({ 150, 300 }));
	
	obstacleList.push_back(obstacle);
	obstacleList.push_back(obstacle1);
	obstacleList.push_back(obstacle2);

	std::shared_ptr<Enemy> enemy(new Enemy({ 300, 400 }));
	std::shared_ptr<Enemy> enemy1(new Enemy({ 450, 400 }));
	std::shared_ptr<Enemy> enemy2(new Enemy({ 150, 400 }));

	enemyList.push_back(enemy);
	enemyList.push_back(enemy1);
	enemyList.push_back(enemy2);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	
	return true;
}

void TwinStickShooterApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	//delete Texture;
}

void TwinStickShooterApp::update(float deltaTime)
{

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		timer += deltaTime;
		if (timer > m_weapon->GetFireRate())
		{
			std::shared_ptr<Bullet> bullet(m_weapon->Fire(deltaTime));
			bulletList.push_back(bullet);
			//m_weapon->Fire(deltaTime);
			timer = 0.0f;
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	if (!(bulletList.empty()))
	{
		for (auto it = bulletList.begin(); it != bulletList.end() || bulletList.empty(); it++)
		{
			(*it)->update(deltaTime); // updates the bullet
		}
		for (auto enemy = enemyList.begin(); enemy != enemyList.end(); enemy++) // loops through the enemies
		{
			for (auto bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
			{ //loops through the bullets for each enemie

				if ((*bullet)->collision((*enemy)))
				{ //if a bullet collides with enemy

					auto bulletcopy = bullet; // make a copy of the bullet
					bullet++;// increase iterator
					bulletList.erase(bulletcopy); // erase the bullet that collided from the list 

					auto enemycopy = enemy;
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
	
	player->update(deltaTime);
	
	for (std::shared_ptr<Enemy> enemy : enemyList) {
		enemy->update(deltaTime, player->getPosition(), obstacleList);
	}
	
}

void TwinStickShooterApp::draw() {
	
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	
	// draw your stuff here!
	
	map->draw(m_2dRenderer);
	for (std::shared_ptr<Enemy> enemy : enemyList) {
		enemy->draw(m_2dRenderer);
	}
	player->draw(m_2dRenderer);
	for (std::shared_ptr<Obstacle> obstacle : obstacleList) {
		obstacle->draw(m_2dRenderer);
	}
	for (std::shared_ptr<Bullet> bullet : bulletList)
	{
		bullet->draw(m_2dRenderer);
	}
	

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}