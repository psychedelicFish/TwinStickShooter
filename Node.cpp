#include "Node.h"

Node::Node(glm::vec2 p, float score)
{
	position = p;
	gscore = score;
	parent = nullptr;
}

glm::vec2 Node::GetPosition() {
	return position;
}

void Node::SetGScore(float score) {
	gscore = score;
}
float Node::GetGScore() {
	return gscore;
}

void Node::SetParent(Node* p) {
	parent = p;
}
Node* Node::GetParent() {
	return parent;
}
