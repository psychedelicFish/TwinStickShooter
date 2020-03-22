#pragma once
#include "Monobehaviour.h"
#include <Texture.h>
#include <list>
class Node;
class Map;
class Player;
class Obstacle;
using ObstacleList = std::list<std::shared_ptr<Obstacle>>;
class Enemy : public Monobehaviour
{
protected:
	aie::Texture* EnemyTexture; //Enemies Texture
	
								//Animation stuff
	float timer = 0.0f; 
	int animationFrame = 0;
	float animationTime = 0.055f;

	//Angle of rotation
	float rotationAngle = 0.f;

	//pathing timer
	float pathTimer = 1.0f;

	float speed;//speed at which the enemy moves
	glm::vec2 desired_velocity;
	glm::vec2 current_velocity;
	glm::vec2 directionToNode;
	glm::vec2 directionToPlayer;
	float attackTime; //How long till the enemy attacks
	float attackTimer; //Timer based off of deltaTime

	float navTimer;

	std::list<Node*> path;

	enum State{PATHING, ATTACKING}; //State Machine
	State state;
	
public:
	Enemy(glm::vec2 pos, std::shared_ptr<aie::Texture> texture); //constructer
	
	bool Active; //Is the enemy active in the scene
	//~Enemy();
	
	void update(float deltaTime, Map& map, Player& player);
	void draw(aie::Renderer2D* renderer) override;
	
	void setPosition(float x, float y); //sets the position of the enemy when released from pooler
	void Attack(Player& player, float deltaTime); //Allows the enemy to attack

	void DirectionToNode();
	void Walk(float deltaTime);
	bool Arrive();
	void CalculateRotation();
	void CalculateVelocity(float deltaTime);


	void AdjustAnimationFrame();

	void QueryPath(Map& map,glm::vec2 PlayerPostion);

	void DirectionToPlayer(glm::vec2 playerPosition);


	//StateMachine TransitionCheck
	bool CheckDistanceFromPlayer(glm::vec2 playerPosition);
};
