#pragma once
#include "Monobehaviour.h"
class Obstacle : public Monobehaviour
{
public:
	Obstacle(glm::vec2 pos, aie::Texture* t); // constucter
	bool Active; //is the obstacle active in the scene
	float getRadius(); // whats the radius of the obstacle - used for collision
	void draw(aie::Renderer2D* renderer);
	void setPosition(float x, float y); //sets the position once active in the scene
	
protected:
	float radius; //radius variable is used in collision detection
};