#include "Node.h"


Node::Node(int row, int col) : row(row), col(col), visited(false), printVisited(false), parent(NULL), parentDirection(NULL)
{
	leftBottomWayPoint = NULL;
	rightBottomWayPoint = NULL;
	leftTopWayPoint = NULL;
	rightTopWayPoint = NULL;
}

Node::~Node()
{
}
