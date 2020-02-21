#pragma once
#include <Renderer2D.h>
#include <Texture.h>
#include <glm/vec2.hpp>
#include <list>
class Node;
class Map
{
private:
	aie::Texture* texture;//Maps image
	//Where the map is located
	float locationX;
	float locationY;
	std::list<Node*> map;
	
public:
	Map();//Constructer
	~Map();//Destructer
	void draw(aie::Renderer2D* renderer);
	void update(float deltaTime, glm::vec2 loc);
};