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
	Bullet(float velocity, glm::vec2 pos, float angle, float life);
	glm::vec2 spriteSize;
	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;
	bool Active;
	float getLife();
	void set(float velocity, glm::vec2 pos, float angle, float life);
	//bool collision(Monobehaviour& other) override;
	float alive;



};