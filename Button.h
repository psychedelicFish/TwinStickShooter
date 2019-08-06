#pragma once
#include <Renderer2D.h>
#include <Font.h>
class Button {
public:
	Button(const char* Text, float x, float y, float width, float height);
	~Button();
	void Draw(aie::Renderer2D* renderer);
	bool Update();
	bool Active;
private:
	aie::Font* font;
	char buttonText[64];

	float posX;
	float posY;
	float m_width;
	float m_height;
};