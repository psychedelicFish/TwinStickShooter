#include <Renderer2D.h>
class HealthBar {
	int maxHealth, currentHealth;
	//Position and size
	float posX;
	float posY;
	float width;
	float height;

public:
	HealthBar(int max, float x, float y, float w, float h); //constructer
	void UpdateHealth(int h); //updates the health bar
	void draw(aie::Renderer2D* renderer, float x, float y);
};