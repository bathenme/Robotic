#include "STC.h"
#include "fstream"
#include "lodepng.h"


using namespace lodepng;


STC::STC(Map &map, Position initialRobotPos) : map(map), initialRobotPos(initialRobotPos)
{
	
	//todo: think how to do this dynamic
	//StcGraph.resize(map.GetCoarseGrid().size()*map.GetCoarseGrid()[0].size() * 2);
}
void STC::resizeGraph(int width, int height)
{
	graph.resize(height);
	for (unsigned int i = 0; i<height; i++)
	{
		graph[i].resize(width);
	}
}


void STC::buildGraph()
{
	int height = map.GetCoarseGrid().size();
	int width = map.GetCoarseGrid()[0].size();
	resizeGraph(width, height);
	vector<vector<bool> > Grid = map.GetCoarseGrid();

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int k = 0; k < width; k++)
		{
			//cout << "this is i: " << i;
			//cout << "this is k: " << k << endl;
			if (!Grid[i][k])
			{	
				graph[i][k] = new Node(i, k);
			}
		}	
	}
}

void STC::AddNeighborsInTree(){
	int height = graph.size();
	int width = graph[0].size();
	//int edgeCount = 0;
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int k = 0; k < width; k++)
		{
			
			if (graph[i][k] != NULL)
			{
				graph[i][k]->graphNeighbors.resize(4);
				//cout << graph[i][k]->row << " " << endl;
				if (i != (height - 1))
				{
					if (graph[i + 1][k] != NULL)
					{
					
						//StcGraph[edgeCount] = Edge(make_pair(i, k), make_pair(i + 1, k));
						//edgeCount++;
						graph[i][k]->graphNeighbors[0] = graph[i + 1][k];
						//graph[i + 1][k]->neighborsInTree[0] = graph[i][k];
					}
				}
				if (k != (width-1))
				{
					if (graph[i][k + 1] != NULL)
					{
						//StcGraph[edgeCount] = Edge(make_pair(i, k), make_pair(i, k+1));
						//edgeCount++;
						graph[i][k]->graphNeighbors[1] = graph[i][k + 1];
						//graph[i][k + 1]->neighborsInTree[1] = graph[i][k];
					}
				}
				if (i >= 1)
				{
					if (graph[i - 1][k] != NULL)
					{
						//StcGraph[edgeCount] = Edge(make_pair(i, k), make_pair(i - 1, k));
						//edgeCount++;
						graph[i][k]->graphNeighbors[2] = graph[i - 1][k];
						//graph[i - 1][k]->neighborsInTree[3] = graph[i][k];
					}

				}
				if (k >= 1)
				{
					if (graph[i][k-1] != NULL)
					{
						//StcGraph[edgeCount] = Edge(make_pair(i, k), make_pair(i, k-1));
						//edgeCount++;
						graph[i][k]->graphNeighbors[3] = graph[i][k - 1];
						//graph[i][k - 1]->neighborsInTree[4] = graph[i][k];
					}
				}
			}
		}
	}
}
void STC::buildSpanningTree()
{
	buildGraph();
	AddNeighborsInTree();

	cout << initialRobotPos.first << " " << initialRobotPos.second;
	DFS(graph[initialRobotPos.first][initialRobotPos.second]);

	
	cout << "done" << endl;
	
}


void STC::DFS(Node *node)
{
	node->visited = true;//since we visited this node

	for (int i = 0; i < node->graphNeighbors.size(); i++)
	{
		node->dfsNeighbors.resize(4);
		if ((node->graphNeighbors[i] != NULL) && (!node->graphNeighbors[i]->visited))
		{
			//node->neighborsInTree[i]->parent = node;
			node->dfsNeighbors[i] = node->graphNeighbors[i];
			if (i == 0){
				node->dfsNeighbors[i]->parentDirection = "bottom";
				node->dfsNeighbors[i]->parent = node;
			}
			else if (i == 1){
				node->dfsNeighbors[i]->parentDirection = "right";
				node->dfsNeighbors[i]->parent = node;
			}
			else if (i == 2){
				node->dfsNeighbors[i]->parentDirection = "top";
				node->dfsNeighbors[i]->parent = node;
			}
			else{
				node->dfsNeighbors[i]->parentDirection = "left";
				node->dfsNeighbors[i]->parent = node;
			}
			DFS(node->dfsNeighbors[i]);
		}
	}

}

void STC::printNodes()
{
	ofstream myRoboticLab;
	myRoboticLab.open("myDfsTree.txt");
	int height = graph.size();
	int width = graph[0].size();
	int StartXposition = initialRobotPos.first;
	int StartYposition = initialRobotPos.second;
	cout << "height: " << height << " width: " << width << " StartXposition: " << StartXposition << " StartYposition: " << StartYposition << endl;

	for (signed int i = 0; i < height; i++)
	{
		for (signed int k = 0; k < width; k++)
		{
			if (graph[i][k] != NULL)
			{
				if (graph[i][k]->visited)
				{
					myRoboticLab << "*";
				}
				else
				{
					myRoboticLab << " ";
				}
			}
			else
			{
				myRoboticLab << " ";
			}
		}
		myRoboticLab << endl;
	}
}

void STC::drawSpanningTree(const char* filePath, vector<unsigned char> image)
{
	bool right = false;
	bool left = false;
	bool top = false;
	bool bottom = false;
	Node* n = graph[initialRobotPos.first][initialRobotPos.second];

	vector<Node* > temp = n->dfsNeighbors;
	stack<Node*, vector<Node* >> nodeStack(n->dfsNeighbors);
	nodeStack.push(n);


	int t = (305 * map.getMapWidth() + 362) * 4;
	image[t] = 255;
	image[t + 1] = 51;
	image[t + 2] = 255;
	encodeOneStep("temp.png", image, map.getMapWidth(), map.getMapHeight());

	while (!nodeStack.empty()){

		Node* node = nodeStack.top();
		nodeStack.pop();
		if (node != NULL)
		{

			//the point on the dfs
			int c = (((node->row * 24) + 12) * map.getMapWidth() + ((node->col * 24) + 12)) * 4;
			//left top
			int l = (((node->row * 24) + 6) * map.getMapWidth() + ((node->col * 24) + 6)) * 4;
			node->leftTopWayPoint = new wayPoint(((node->col * 24) + 6), ((node->row * 24) + 6));
			//right top
			int m = (((node->row * 24) + 6) * map.getMapWidth() + ((node->col * 24) + 18)) * 4;
			node->rightTopWayPoint = new wayPoint(((node->col * 24) + 18), ((node->row * 24) + 6));
			//left bottom
			int n = (((node->row * 24) + 18) * map.getMapWidth() + ((node->col * 24) + 6)) * 4;
			node->leftBottomWayPoint = new wayPoint(((node->col * 24) + 6), ((node->row * 24) + 18));
			//right bottom
			int o = (((node->row * 24) + 18) * map.getMapWidth() + ((node->col * 24) + 18)) * 4;
			node->rightBottomWayPoint = new wayPoint(((node->col * 24) + 18), ((node->row * 24) + 18));
			image[l] = 51;
			image[l + 1] = 153;
			image[l + 2] = 255;

			image[m] = 51;
			image[m + 1] = 153;
			image[m + 2] = 255;

			image[n] = 51;
			image[n + 1] = 153;
			image[n + 2] = 255;

			image[o] = 51;
			image[o + 1] = 153;
			image[o + 2] = 255;

			image[c] = 255;
			image[c + 1] = 0;
			image[c + 2] = 0;

			if (node->dfsNeighbors[0] != NULL){
				nodeStack.push(node->dfsNeighbors[0]);
				int d = (((node->dfsNeighbors[0]->row * 24) + 12) * map.getMapWidth() + ((node->dfsNeighbors[0]->col * 24) + 12)) * 4;
				for (int i = c; i < d; i+=(map.getMapWidth()*4)){
					image[i] = 255;
					image[i + 1] = 0;
					image[i + 2] = 0;
				}
				bottom = true;
			}
				
			if (node->dfsNeighbors[1] != NULL){
				nodeStack.push(node->dfsNeighbors[1]);
				int d = (((node->dfsNeighbors[1]->row * 24) + 12) * map.getMapWidth() + ((node->dfsNeighbors[1]->col * 24) + 12)) * 4;
				for (int i = c; i < d; i += 4){
					image[i] = 255;
					image[i + 1] = 0;
					image[i + 2] = 0;
				}
				right = true;
				
			}
			if (node->dfsNeighbors[2] != NULL){
				nodeStack.push(node->dfsNeighbors[2]);
				int d = (((node->dfsNeighbors[2]->row * 24) + 12) * map.getMapWidth() + ((node->dfsNeighbors[2]->col * 24) + 12)) * 4;
				for (int i = d; i < c; i += (map.getMapWidth() * 4)){
					image[i] = 255;
					image[i + 1] = 0;
					image[i + 2] = 0;
				}
				top = true;
			}
			if (node->dfsNeighbors[3] != NULL){
				nodeStack.push(node->dfsNeighbors[3]);
				int d = (((node->dfsNeighbors[3]->row * 24) + 12) * map.getMapWidth() + ((node->dfsNeighbors[3]->col * 24) + 12)) * 4;
				for (int i = d; i < c; i += 4){
					image[i] = 255;
					image[i + 1] = 0;
					image[i + 2] = 0;
				}
				left = true;
			}
			if (node->parent != NULL)
			{
				if (right &&!left && !top && !bottom && node->parentDirection == "right"){
					node->parent->rightTopWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->parent->rightBottomWayPoint);
					
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
				}
				else if (bottom && !right && !left && !top && node->parentDirection == "right"){
					node->parent->rightTopWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->parent->rightBottomWayPoint);

					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
				else if (right && !left && !top && !bottom && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (top && !right && !left && !bottom && node->parentDirection == "right"){
					node->parent->rightTopWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->parent->rightBottomWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
				else if (top && !right && !left && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
				else if (left && right && !top && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (bottom && !right && !left && !top && node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (left && !right && !top && !bottom && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
				}
				else if (top && !right && !left && !bottom && node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (left && !right && !top && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (!right && !left && !top && !bottom && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (bottom && left && !right && !top && node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (left && !bottom &&  !right && !top &&node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (!right && !left && !top && !bottom && node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (bottom && !left && !right && !top && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (left && right && !bottom && !top && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
				}
				else if (bottom && top && !left && !right && node->parentDirection == "right"){
					node->parent->rightTopWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->parent->rightBottomWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
				else if (right && !left && !top && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (right && top && !left && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (top && bottom && !right && !left && node->parentDirection == "left"){
					node->parent->leftBottomWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->parent->leftTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else if (left && bottom && !right && !top && node->parentDirection == "bottom"){
					node->parent->rightBottomWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->parent->leftBottomWayPoint);

					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
				else if (!right && !left && !bottom && !top && node->parentDirection == "right"){
					node->parent->rightTopWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->parent->rightBottomWayPoint);

					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
				}
				else if (!right && !left && !top && !bottom && node->parentDirection == "top"){
					node->parent->leftTopWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->parent->rightTopWayPoint);

					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
			}
			else{
				if (right){
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
				}
				else if (left){
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
				}
				else if (bottom){
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
					node->rightBottomWayPoint->setNextWayPoint(node->leftBottomWayPoint);
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
				}
				else{
					node->leftBottomWayPoint->setNextWayPoint(node->leftTopWayPoint);
					node->leftTopWayPoint->setNextWayPoint(node->rightTopWayPoint);
					node->rightTopWayPoint->setNextWayPoint(node->rightBottomWayPoint);
				}
			}
		}
		
		left = right = bottom = top = false;
		
	}	
	drawWayPoints(image);
	encodeOneStep(filePath, image, map.getMapWidth(), map.getMapHeight());
}


void STC::drawWayPoints(vector<unsigned char>& image){
	Node* n = graph[initialRobotPos.first][initialRobotPos.second];
	stack<wayPoint* > wayPointStack;
	wayPointStack.push(n->leftTopWayPoint);
	while (!wayPointStack.empty()){

		wayPoint* waypoint = wayPointStack.top();
		wayPointStack.pop();
		//cout << "col: "<< waypoint->getX() << " " << "row: " << waypoint->getY() << endl;
		if (waypoint != NULL)
		{
			int s = ((waypoint->getY() * map.getMapWidth()) + waypoint->getX()) * 4;
			int d = ((waypoint->getNext()->getY() * map.getMapWidth()) + waypoint->getNext()->getX()) * 4;
			if (waypoint->getNext()->getY() == waypoint->getY()){
				if (waypoint->getNext()->getX() > waypoint->getX()){
					for (int i = s; i < d; i += 4){
						image[i] = 255;
						image[i + 1] = 255;
						image[i + 2] = 102;
					}
				}
				else{
					for (int i = d; i < s; i += 4){
						image[i] = 255;
						image[i + 1] = 255;
						image[i + 2] = 102;
					}
				}

			}
			if (waypoint->getNext()->getX() == waypoint->getX()){
				if (waypoint->getNext()->getY() > waypoint->getY()){
					for (int i = s; i < d; i += (map.getMapWidth() * 4)){
						image[i] = 255;
						image[i + 1] = 255;
						image[i + 2] = 102;
					}
				}
				else{
					for (int i = d; i < s; i += (map.getMapWidth() * 4)){
						image[i] = 255;
						image[i + 1] = 255;
						image[i + 2] = 102;
					}
				}

			}
		}
		if (waypoint->getNext()->getX() == n->leftTopWayPoint->getX()
			&& waypoint->getNext()->getY() == n->leftTopWayPoint->getY()){
			break;
		}
		else{
			wayPointStack.push(waypoint->getNext());
		}
		
	}


}
void STC::encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

vector<vector<Node *> >& STC::getNodeGraph(){
	return graph;
}




STC::~STC()
{
}
