#define _USE_MATH_DEFINES
#include "Player.h"
#include "Bullet.h"
#include <Input.h>
#include <math.h>
#include "Weapon.h"
#include "Enemy.h"
#include <glm/glm.hpp>




Player::Player() : Monobehaviour({ 720/2, 720/2 },textureManager.GetTexture("./bin/textures/Player_stand.png"), 1, 1, glm::vec2{ 1,1 })
{
	speed = 200.0f;
	velocity = { 0,0 };
	rotation = 0.0f;
	weapon.reset(new Weapon(position.x, position.y, rotation));
	lightOverlay = textureManager.GetTexture("./bin/textures/CharacterLight.png");
	float width = Texture->getWidth();
	float height = Texture->getHeight();
	spriteSize = { width, height };
	MaxHealth = 100;
	currentHealth = MaxHealth;
	Alive = true;
}
Player::~Player()
{
	//delete playerTexture;
}

void Player::Update(float deltaTime, float x, float y)
{
	aie::Input* input = aie::Input::getInstance();

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
	position.x += velocity.x * deltaTime;//Update X position
	position.y += velocity.y * deltaTime;//Update Y position

	glm::vec2 mousePos = { input->getMouseX(), input->getMouseY()};

	glm::vec2 rotationVec = mousePos - position;
	
	rotationVec = glm::normalize(rotationVec);
	rotation = acos(rotationVec.x);

	if (rotationVec.y < 0) {
		rotation = glm::radians(360.f) - rotation;
	}

	weapon->update(deltaTime, position.x, position.y, rotation);
	
}

	void Player::draw(aie::Renderer2D* renderer) {
		renderer->drawSprite(lightOverlay.get(), position.x, position.y, 0, 0, rotation);
		renderer->drawSprite(Texture.get(), position.x, position.y, 0, 0, rotation);
	}
	void Player::TakeDamage(int dmg) {
		assert(dmg >= 0);
		currentHealth -= dmg;
		if (currentHealth <= 0) {
			Alive = false;
		}

	}
	int Player::GetMaxHealth() {
		return MaxHealth;
	}
	int Player::getCurrentHealth() {
		return currentHealth;
	}


