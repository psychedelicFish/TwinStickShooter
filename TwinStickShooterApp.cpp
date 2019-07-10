#include "TwinStickShooterApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "Weapon.h"



TwinStickShooterApp::TwinStickShooterApp() {
	//playerTexture = new aie::Texture("./textures/car.png");
	
	
}

TwinStickShooterApp::~TwinStickShooterApp() {
	//delete playerTexture;
}

bool TwinStickShooterApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	enemy = new Enemy();
	player.reset(new Player(enemy));
	map = new Mape();
	m_weapon = player->weapon; 
	

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

void TwinStickShooterApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
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
	if (!(bulletList.empty())) {
		for (auto it = bulletList.begin(); it != bulletList.end(); it++)
		{
			(*it)->update(deltaTime);
			if ((*it)->collision(enemy)) {
				bulletList.erase(it);
				break;
			}
		}
	}
	player->update(deltaTime);
	enemy->update(deltaTime, player->getPosition());
	
}

void TwinStickShooterApp::draw() {
	
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	
	// draw your stuff here!
	
	map->draw(m_2dRenderer);
	enemy->draw(m_2dRenderer);
	player->draw(m_2dRenderer);
	for (std::shared_ptr<Bullet> bullet : bulletList)
	{
		bullet->draw(m_2dRenderer);
	}
	

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}