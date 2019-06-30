#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Renderer2D.h>
class Monobehaviour
{
protected:
	glm::vec2 position;
	
public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(aie::Renderer2D* renderer) = 0;
	virtual bool collision(Monobehaviour& other);
};
