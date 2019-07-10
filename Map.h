#pragma once
#include <Renderer2D.h>
#include <Texture.h>
class Mape
{
private:
	aie::Texture* texture;
public:
	Mape();
	void draw(aie::Renderer2D* renderer);
};