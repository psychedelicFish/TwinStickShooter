#include "HealthBar.h"
#include <iostream>

HealthBar::HealthBar(int max, float x, float y, float w, float h) { //constuct the buttoln
	posX = x;
	posY = y;
	width = w;
	height = h;
	
	maxHealth = max;
	currentHealth = maxHealth;
}
void HealthBar::UpdateHealth(int h) { //updates the bars health variable 
	currentHealth = h;
	if (currentHealth < 0) {
		currentHealth = 0;
	}
}
void HealthBar::draw(aie::Renderer2D* renderer, float x, float y) {
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawBox(x, y, width, height);

	float ratio = currentHealth / (float)maxHealth; //need a ratio so the bar looks filled nicely 
	//std::cout << ratio << std::endl; //testing purposes
	float healthFull = width * ratio; //sets how full the bar is 
	//std::cout << healthFull << std::endl; //testing purposes 

	float offsetX = x - (width - healthFull) * 0.5f; //offsets the bar based on how big it is 
	
	renderer->setRenderColour(0, 1, 0, 1);
	renderer->drawBox(offsetX, y, healthFull, height);
	renderer->setRenderColour(1, 1, 1, 1);

}