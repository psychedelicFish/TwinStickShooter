#include "Player.h"
#include <Input.h>


Player::Player(aie::Texture* texture)
{
	position = { 100, 100 };
	speed = 100.0f;
	velocity = { 0,0 };
	rotation = 0.0f;
	timer = 0.0f;
	Texture = texture;

}
void Player:: update(float deltaTime)
{	
	timer += deltaTime;
	aie::Input* input = aie::Input::getInstance();
	//PlayerMovement
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

}
void Player::draw(aie::Renderer2D* renderer) {
	
	renderer->setRenderColour(1, 1, 0, 1);
	renderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	//renderer->drawSprite(texture, position.x, position.y, 0, 0);
	//renderer->drawCircle(position.x, position.y, 10);
	//renderer->drawLine(position.x, position.y, position.x + 20, position.y + 20);
	
}