#pragma once
#include "Monobehaviour.h"
class Obstacle : public Monobehaviour
{
public:
	Obstacle(glm::vec2 pos);
	float getRadius();
	
protected:
	float radius;
};