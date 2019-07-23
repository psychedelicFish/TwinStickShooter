#define _USE_MATH_DEFINES
#include "Player.h"
#include "Bullet.h"
#include <Input.h>
#include <math.h>
#include "Weapon.h"
#include "Enemy.h"
#include <glm/glm.hpp>



Player::Player() : Monobehaviour({ 100, 100 },"../bin/textures/Player_stand.png", 1, 1, glm::vec2{ 1,1 })
{
	speed = 200.0f;
	velocity = { 0,0 };
	rotation = 0.0f;
	weapon = new Weapon(position.x, position.y, rotation);
	//m_enemy = enemy;
	//playerTexture = new aie::Texture("../bin/textures/Player_stand.png");
	lightOverlay = new aie::Texture("../bin/textures/CharacterLight.png");
	float width = texture->getWidth();
	float height = texture->getHeight();
	spriteSize = { width, height };
}
Player::~Player()
{
	//delete playerTexture;
}

void Player::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	//mousePosition = input->getMouseXY;
	//PlayerMovement
	
	glm::vec2 mousePos = { input->getMouseX(), input->getMouseY() };
	glm::vec2 rotationVec = mousePos - position;

	rotationVec = glm::normalize(rotationVec);
	rotation = acos(rotationVec.x);
	
	if (rotationVec.y < 0) {
		rotation = glm::radians(360.f) - rotation;
	}

	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//{
		//rotation++;
		//if (rotation > 360)
		//{
			//rotation = 0;
		//}
	//}
	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	
		//rotation--;
		//if (rotation < -360)
		//{
			//rotation = 0;
		//}
	//}
	if (input->isKeyDown(aie::INPUT_KEY_A)) // Left
	{
		velocity.x = -speed;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_D)) //Right
	{
		velocity.x = speed;
	}
	else
	{
		velocity.x = 0.0f;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S)) // Down
	{
		velocity.y = -speed;
	}
	else if (input->isKeyDown(aie::INPUT_KEY_W))//Up
	{
		velocity.y = speed;
	}
	else {
		velocity.y = 0.0f;
	}
	position.x += velocity.x * deltaTime;//Update X powsition
	position.y += velocity.y * deltaTime;//Update Y position

	weapon->update(deltaTime, position.x, position.y, rotation);
	
}

	void Player::draw(aie::Renderer2D* renderer) {
		//int width = DownTexture->getWidth() / 5;
		//renderer->setRenderColour(1, 1, 0, 1);
		renderer->drawSprite(lightOverlay, position.x, position.y, 0, 0, rotation);
		renderer->drawSprite(texture, position.x, position.y, 0, 0, rotation);

		//renderer->drawCircle(position.x, position.y, 10);
		//renderer->drawLine(position.x, position.y, position.x + 20, position.y + 20);

	}


