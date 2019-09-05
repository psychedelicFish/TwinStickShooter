#pragma once
#include <Renderer2D.h>
#include <Texture.h>
#include <glm/vec2.hpp>
#include <list>
class TileObjectPool;
class Tile;
class Map
{
private:
	aie::Texture* texture;//Maps image
	//Where the map is located
	float locationX;
	float locationY;
public:
	Map();//Constructer
	~Map();//Destructer
	void draw(aie::Renderer2D* renderer);
	void update(float deltaTime, glm::vec2 loc);
};