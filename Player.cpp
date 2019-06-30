#define _USE_MATH_DEFINES
#include "Player.h"
#include "Bullet.h"
#include <Input.h>
#include <math.h>
#include "Weapon.h"


Player::Player()
{
	position = { 100, 100 };
	speed = 200.0f;
	velocity = { 0,0 };
	rotation = 0.0f;
	timer = 10.0f;
	weapon = new Weapon(position.x, position.y, rotation);
	playerTexture = new aie::Texture("../bin/textures/Player_stand.png");
	float width = playerTexture->getWidth();
	float height = playerTexture->getHeight();
	spriteSize = { width, height };
}
Player::~Player()
{
	delete playerTexture;
}

void Player:: update(float deltaTime)
{	
	aie::Input* input = aie::Input::getInstance();
	//mousePosition = input->getMouseXY;
	//PlayerMovement
	
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		timer += deltaTime;
		if (timer > weapon->GetFireRate())
		{
 			weapon->Fire(deltaTime);
			timer = 0.0f;
		}	
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		rotation = rotation++;
		if(rotation > 360)
		{ 
			rotation = 0;
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		rotation = rotation - 1;
		if(rotation < -360)
		{
			rotation = 0;
		}
	}
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
	else if(input->isKeyDown(aie::INPUT_KEY_W))//Up
	{
		velocity.y = speed;
	}
	else {
		velocity.y = 0.0f;
	}
	position.x += velocity.x * deltaTime;//Update X position
	position.y += velocity.y * deltaTime;//Update Y position
	weapon->update(deltaTime, position.x, position.y, rotation);
}
void Player::draw(aie::Renderer2D* renderer) {
	//int width = DownTexture->getWidth() / 5;
	//renderer->setRenderColour(1, 1, 0, 1);
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawSprite(playerTexture, position.x, position.y, 0, 0, (rotation * M_PI)/180);
	renderer->setUVRect(0, 0, 1, 1);

	for (Bullet* bullet : weapon->bulletList)
	{
		bullet->draw(renderer);
	}
	//renderer->drawCircle(position.x, position.y, 10);
	//renderer->drawLine(position.x, position.y, position.x + 20, position.y + 20);
	
}