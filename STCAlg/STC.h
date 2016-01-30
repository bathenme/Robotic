/*
 * STC.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef STC_H_
#define STC_H_
#include <vector>
#include "../Map/Node.h"
#include "../Map/Map.h"
#include "iostream"
#include "../Map/lodepng.h"
#include "../Map/wayPoint.h"


using namespace std;

typedef pair<double, double> Position;
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




#endif /* STC_H_ */
