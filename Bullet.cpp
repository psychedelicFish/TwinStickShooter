#include "Bullet.h"
#include <math.h>


Bullet ::Bullet(float velocity, glm::vec2 pos, float angle, float life) 
	: Monobehaviour(pos, textureManager.GetTexture("./bin/textures/bullets_colored_edit.png"), 1, 1, glm::vec2{ 9,9 })
{
	Active = false; //set the bullet to inactive on creation
	Velocity = velocity; //set the velocity to the passed in variable
	Angle = angle; // set the bullets angle
	bulletLife = life; // set how long it will survive
	alive = 0; //intialise how long it has been alive
}
//This function is similar to the constructer only it is called when the weapon is fired.
//It is needed to reset the bullets stats when it comes from the pooler
//in case it retains any of the values from when it was previously used
void Bullet:: set(float velocity, glm::vec2 pos, float angle, float life) {
	Velocity = velocity; 
	Angle = angle;
	bulletLife = life;
	position = pos;
	alive = 0;
}

void Bullet:: update(float deltaTime)
{
	alive += deltaTime; //increase how long it has been alice
	position.x = position.x + (Velocity * cos(Angle)); // move it in the x
	position.y = position.y + (Velocity * sin(Angle)); // move it in the y
}
void Bullet:: draw(aie::Renderer2D* renderer)
{
	renderer->setUVRect(0.f, 0.f, 1.f, 1.f);
	renderer->drawSprite(Texture.get(), position.x, position.y);;
}
float Bullet::getLife() {
	return bulletLife;
}
