#pragma once

#include <vector>
#include <stack>
#include "wayPoint.h"
using namespace std;
class Node {
public:
	vector<Node *> graphNeighbors;
	vector<Node* > dfsNeighbors;
	wayPoint * leftTopWayPoint;
	wayPoint * rightTopWayPoint;
	wayPoint * leftBottomWayPoint;
	wayPoint * rightBottomWayPoint;
	Node* parent;
	const char* parentDirection;
	int row, col;
	bool visited;
	bool printVisited;
	Node(int row, int col);
	~Node();
};


