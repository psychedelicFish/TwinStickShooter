#pragma once
#include <Renderer2D.h>
#include <Texture.h>
class Map
{
private:
	aie::Texture* texture;
public:
	Map();
	void draw(aie::Renderer2D* renderer);
};