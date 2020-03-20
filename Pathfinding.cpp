#include "Pathfinding.h"
#include <exception>
#include <algorithm>
#include <iostream>
#include "Map.h"
#include "Queue.h"


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

void Node::Draw(aie::Renderer2D * r)
{
	r->drawCircle(position.x, position.y, 5.f);
}

namespace std {
	bool less(Node* i, Node* j) {
		return (i->GetGScore() < j->GetGScore());
	}
}

std::list<Node*> Pathfinder::findPath(Node* start, Node* end)
{
	std::list<Node*> path;
	if (start == nullptr || end == nullptr) {
		return path;
	}
	if (start == end) {
		return path;
	}
	start->SetGScore(0);
	start->SetParent(nullptr);
	
	Queue<Node*> openList;

	std::list<Node*> closedList;

	openList.push(start);

	while (!openList.empty()) {

		Node* currentNode = openList.top();

		if (currentNode == end) {
			break;
		}

		openList.pop();
		closedList.push_back(currentNode);

		for (Edge e : currentNode->connections) {
			
			auto i = std::find(closedList.begin(), closedList.end(), e.target);
			if(i == closedList.end()){
				float gscore = currentNode->GetGScore() + e.cost;
				
				auto j = std::find(openList.begin(), openList.end(), e.target);
				if (j == openList.end()) {
					e.target->SetGScore(gscore);
					e.target->SetParent(currentNode);
					openList.push(e.target);
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

void Pathfinder::AddNodeToList(Node* n) {
	nodes.push_back(n);
}

void Pathfinder::SetUpEdges(const TileList &m) {

	for (auto y = 0; y < mapy; y++) {
		for (auto x = 0; x < mapx; x++) {
			Node* newnode = nodes[y * mapx + x];

			if (!newnode) {
				continue;
			}

			for (int oy = -1; oy < 2; ++oy) {
				for (int ox = -1; ox < 2; ++ox) {
					if (x + ox >= 0 &&
						x + ox < mapx &&
						y + oy >= 0 &&
						y + oy < mapy &&
						nodes[(y + oy) * mapx + x + ox] != nullptr &&
						!(ox == 0 && oy == 0) && m[(y + oy) * mapx + x + ox]->passable) {

							float cost = (ox != 0 && oy != 0) ? 1.414f : 1.f;
							newnode->connections.push_back(Edge{ nodes[(y + oy) * mapx + x + ox], cost });

					}
				}

			}
		}
	}
}

Pathfinder::Pathfinder(int x, int y) {
	mapx = x;
	mapy = y;
}
void Pathfinder::Draw(aie::Renderer2D * r) {
}

Node* Pathfinder::ReturnNodeByIndex(int i) {
	return nodes[i];
}

void Pathfinder::ResetNodeGScores() {
	for (Node* n : nodes) {
		n->SetGScore(100000.f);
	}
}
