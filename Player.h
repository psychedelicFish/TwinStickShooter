#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
class Player : Monobehaviour
{
	aie::Renderer2D* m_2dRenderer;
	glm::vec2 velocity;
	float speed;
	float rotation;
	float timer;
	aie::Texture* Texture;
public:
	Player(aie::Texture* texture);
	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;
};
