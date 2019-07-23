#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Renderer2D.h>
#include <Texture.h>
class Monobehaviour
{
protected:
	glm::vec2 position;
	aie::Texture* texture;
	float sizeX;
	float sizeY;
	float frameX;
	float frameY;
	
	
public:
	Monobehaviour(glm::vec2 pos, char* FileName, int X, int Y, glm::vec2 size);
	~Monobehaviour();
	glm::vec2 getPosition();
	
	bool collision(std::shared_ptr<Monobehaviour> other);
	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
	float getX();
	float getY();
	float getSizeX();
	float getSizeY();
	virtual void die();

	//virtual bool collision(Monobehaviour& other);
};
