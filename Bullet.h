#pragma once
#include "Monobehaviour.h" 
#include <Texture.h>
class Bullet : public Monobehaviour
{
protected:
	float Velocity;
	float Angle;
	//aie::Texture* texture;
	float bulletLife;
	
public:
	Bullet(float velocity, float x, float y, float angle, float life);
	glm::vec2 spriteSize;
	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;
	//bool collision(Monobehaviour& other) override;



};