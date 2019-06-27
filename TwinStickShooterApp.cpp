#include "TwinStickShooterApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


TwinStickShooterApp::TwinStickShooterApp() {
	playerTexture = new aie::Texture("./textures/car.png");
	player = new Player(playerTexture);
}

TwinStickShooterApp::~TwinStickShooterApp() {
	delete playerTexture;
	delete player;
}

bool TwinStickShooterApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	

	return true;
}

void TwinStickShooterApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void TwinStickShooterApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	player->update(deltaTime);
}

void TwinStickShooterApp::draw() {
	
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawLine(1, 1, 50, 50);
	player->draw(m_2dRenderer);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}