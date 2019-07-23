#include "Bullet.h"
#include <math.h>


Bullet ::Bullet(float velocity, glm::vec2 pos, float angle, float life) 
	: Monobehaviour(pos, "../bin/textures/bullets_colored_edit.png", 1, 1, glm::vec2{ 9,9 })
{
	
	Velocity = velocity;
	Angle = angle;
	bulletLife = life;
}

void Bullet:: update(float deltaTime)
{
	position.x = position.x + (Velocity * cos(Angle));
	position.y = position.y + (Velocity * sin(Angle));
	//if(collision())
}
void Bullet:: draw(aie::Renderer2D* renderer)
{
	renderer->setUVRect(0.f, 0.f, 1.f, 1.f);
	renderer->drawSprite(texture, position.x, position.y);;
}
