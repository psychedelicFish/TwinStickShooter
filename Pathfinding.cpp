#include "Pathfinding.h"
#include <exception>
#include <algorithm>

Node::Node(glm::vec2 p, bool pass)
{
	position = p;
	passable = pass;
}

void Node::SetGScore(int score) {
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

void Node::Draw(aie::Renderer2D * r)
{
	if (passable) {
		r->drawSprite(passableTexture, position.x, position.y);
	}
	else {
		r->drawSprite(impassableTexture, position.x, position.y);
	}
	
}

std::list<Node*> Pathfinder::findPath(Node* start, Node* end)
{
	std::list<Node*> path;
	if (start == nullptr || end == nullptr) {
		throw std::runtime_error("start node or end node does not exist");
	}
	if (start == end) {
		return path;
	}
	start->SetGScore(0);
	start->SetParent(nullptr);

	std::list<Node*> openList;
	std::list<Node*> closedList;

	openList.push_back(start);

	while (!openList.empty()) {
		std::sort(openList.begin(), openList.end());

		Node* currentNode = *openList.begin();

		if (currentNode == end) {
			return path;
		}
		openList.remove(currentNode);
		closedList.push_back(currentNode);

		for each(Edge e in currentNode->connections) {
			
			auto i = std::find(closedList.begin(), closedList.end(), e.target);
			if(i == closedList.end()){
				float gscore = currentNode->GetGScore() + e.cost;

				auto j = std::find(openList.begin(), openList.end(), e.target);
				if (j == openList.end()) {
					e.target->SetGScore = gscore;
					e.target->SetParent(currentNode);
					openList.push_back(e.target);
				}
				else if (gscore < e.target->GetGScore()) {
					e.target->SetGScore(gscore);
					e.target->SetParent(currentNode);
				}

			}
		}
	}

	auto currentNode = end;

	while (currentNode != nullptr) {
		path.push_front(currentNode);
		currentNode = currentNode->GetParent();
	}

	return path;
}
