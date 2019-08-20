#include "Button.h"
#include <string.h>
#include <iostream>
#include <Input.h>

Button::Button(const char* Text, float x, float y, float width, float height) {

	strcpy_s(buttonText, 64, Text);
	font = new aie::Font("./bin/fonts/consolas.ttf", 24);

	posX = x;
	posY = y;
	m_width = width;
	m_height = height;
}
Button::~Button() {
	delete font;
}
void Button::Draw(aie::Renderer2D* renderer) {
	
	renderer->setRenderColour(0.0f, 0.0f, 0.0f, 0.0f);
	renderer->drawBox(posX, posY, m_width, m_height);
	renderer->setRenderColour(0.0f, 0.0f, 1.0f, 1.0f);
	
	float textWidth = font->getStringWidth(buttonText);
	float textHeight = font->getStringHeight(buttonText);
	float centredPosX = posX - (textWidth * 0.5f) + 2;
	float centredPosY = posY - (textHeight * 0.5f) + 5;
	
	renderer->drawText(font, buttonText, centredPosX, centredPosY);
}
bool Button::Update() {
	aie::Input* input = aie::Input::getInstance();

	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	float left = posX - (m_width * 0.5f);
	float right = posX + (m_width * 0.5f);
	float bottom = posY - (m_height * 0.5f);
	float top = posY + (m_height * 0.5f);

	if (mouseX > left && mouseX < right && mouseY > bottom && mouseY < top) {
		return input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT);
	}
	else {
		return false;
	}

}