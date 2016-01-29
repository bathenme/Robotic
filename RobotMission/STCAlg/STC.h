#ifndef STC_H
#define STC_H
#include "iostream"
#include <vector>
#include "../Map/Node.h"
#include "../Map/Map.h"
#include "../Map/lodepng.h"
#include "../Map/wayPoint.h"



using namespace std;

typedef pair<int, int> Position;
//typedef pair<Position, Position> Edge;
class STC {
private:
	Map &map;
	Position initialRobotPos;
	vector<vector<Node *> > graph;


	
	//vector<Edge> StcGraph;
	void resizeGraph(int width, int height);
	void buildGraph();
	void DFS(Node *node);
	void AddNeighborsInTree();
	void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
	void makeWayPointsVector();
public:

	STC(Map &map, Position initialRobotPos);
	void buildSpanningTree();
	void printNodes();
	void drawSpanningTree(const char* filePath, vector<unsigned char> image);
	void drawWayPoints(vector<unsigned char>& image);
	vector<vector<Node *> >& getNodeGraph();
	virtual ~STC();
};

#endif
