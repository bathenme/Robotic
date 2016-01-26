#include "Node.h"


Node::Node(int row, int col) : row(row), col(col), visited(false), printVisited(false), parent(NULL), parentDirection(NULL)
{
	 leftBottomWayPoint = NULL;
	 leftTopWayPoint = NULL;
	 rightBottomWayPoint = NULL;
	 rightTopWayPoint = NULL;
}

Node::~Node()
{
}
