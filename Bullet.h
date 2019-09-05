#pragma once
#include "Monobehaviour.h" 
#include <Texture.h>
class Bullet : public Monobehaviour
{
protected:
	float Velocity; //speed of bullet
	float Angle; //angle of travel
	float bulletLife;//how long the bullet stays in scene
	
	
	
public:
	Bullet(float velocity, glm::vec2 pos, float angle, float life);//constructer
	
	glm::vec2 spriteSize; //How big is the bullet
	
	void update(float deltaTime) override; //update overridden from Monobehaviour
	void draw(aie::Renderer2D* renderer) override; //draw overridden from Monobehaviour
	bool Active; //Is the bullet active in the scene
	float getLife(); //Get the bulletLife variable
	void set(float velocity, glm::vec2 pos, float angle, float life); //set the bullet in the scene
	//bool collision(Monobehaviour& other) override;
	float alive; //time the bullet has been alive



};