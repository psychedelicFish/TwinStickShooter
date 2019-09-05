#pragma once
#include <Renderer2D.h>
#include <Font.h>
class Button {
public:
	Button(const char* Text, float x, float y, float width, float height); // constructer
	~Button(); //destructer
	void Draw(aie::Renderer2D* renderer); //Draw function called every frame
	bool Update(); // Update function called every frame
	bool Active; //is the button in the scene
private:
	aie::Font* font; //font used for the button
	char buttonText[64]; // container for the text that the button has

	//Postion and size variables
	float posX;
	float posY;
	float m_width;
	float m_height;
};