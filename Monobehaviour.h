#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Renderer2D.h>
#include <Texture.h>
#include "TextureManager.h"
class Monobehaviour //base class for some objects
{
protected:
	glm::vec2 position; //where the object is
	std::shared_ptr<aie::Texture> Texture; // what the object looks like
	//How big the object is
	float sizeX;
	float sizeY;
	//Animation stuff
	float frameX;
	float frameY;
	
	
public:
	Monobehaviour(glm::vec2 pos, std::shared_ptr<aie::Texture> texture, int X, int Y, glm::vec2 size);//constructer 
	Monobehaviour(glm::vec2 pos, int X, int Y, glm::vec2 size); //constructer for when object handles its own texture
	~Monobehaviour(); // destructer
	glm::vec2 getPosition(); //return the objects position
	
	bool collision(std::shared_ptr<Monobehaviour> other); //handles collision logic
	virtual void update(float deltaTime); //update more then likely overridden
	virtual void draw(aie::Renderer2D* renderer); // draw more then likely overriden
	//Returns one of the positions varibles
	float getX();
	float getY();
	//Returns the size varibles of the object - used in collision
	float getSizeX();
	float getSizeY();
	//kill the object
	virtual void die();
};
