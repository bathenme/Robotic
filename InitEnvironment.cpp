#include "InitEnvironment.h"


InitEnvironment::InitEnvironment(const char* parametersFile){
	ifstream paramfile(parametersFile);
	string line;
	char delimiter = ':';
	while (getline(paramfile, line))
	{
		if (line.empty()) {
			break;
		}
		vector<string> params = split(line, delimiter);
		if (params[0] == "map"){
			// trim from start
			params[1].erase(params[1].begin(), find_if(params[1].begin(), params[1].end(), not1(ptr_fun<int, int>(isspace))));
			// trim from end
			params[1].erase(find_if(params[1].rbegin(), params[1].rend(), not1(ptr_fun<int, int>(isspace))).base(), params[1].end());

			mapImg = params[1];
		}
		else if (params[0] == "startLocation"){
			// trim from start
			params[1].erase(params[1].begin(), find_if(params[1].begin(), params[1].end(), not1(ptr_fun<int, int>(isspace))));
			// trim from end
			params[1].erase(find_if(params[1].rbegin(), params[1].rend(), not1(ptr_fun<int, int>(isspace))).base(), params[1].end());

			vector<string> loc = split(params[1], ' ');

			int col = atoi(loc.at(0).c_str()); 
			int row = atoi(loc.at(1).c_str());
			startLocation.location = make_pair(row, col);
			startLocation.yaw = stod(loc.at(2).c_str());

		}
		else if (params[0] == "robotSize"){
			// trim from start
			params[1].erase(params[1].begin(), find_if(params[1].begin(), params[1].end(), not1(ptr_fun<int, int>(isspace))));
			// trim from end
			params[1].erase(find_if(params[1].rbegin(), params[1].rend(), not1(ptr_fun<int, int>(isspace))).base(), params[1].end());

			vector<string> size = split(params[1], ' ');

			double hieght = stod(size.at(0).c_str());
			double width = stod(size.at(1).c_str());
			robotSize = make_pair(hieght/100, width/100);

		}
		else if (params[0] == "MapResolutionCM"){
			// trim from start
			params[1].erase(params[1].begin(), find_if(params[1].begin(), params[1].end(), not1(ptr_fun<int, int>(isspace))));
			// trim from end
			params[1].erase(find_if(params[1].rbegin(), params[1].rend(), not1(ptr_fun<int, int>(isspace))).base(), params[1].end());

			double resolution = stod(params[1].c_str());
			MapResolution = resolution / 100;
		}

		
	}

	m = new Map(getMapResolution(), getRobotSize());
	m->loadMapFromFile(getMapImage().c_str());
	m->buildGrid(m->getRobotSizeInCells(), m->GetFineGrid());
	m->buildGrid((m->getRobotSizeInCells() * 2), m->GetCoarseGrid());
	m->printGrid(m->GetFineGrid(), (m->getMapHeight() / m->getRobotSizeInCells())
		, (m->getMapWidth() / m->getRobotSizeInCells()), "finegrid.txt");
	m->printGrid(m->GetCoarseGrid(), (m->getMapHeight() / (m->getRobotSizeInCells() * 2))
		, (m->getMapWidth() / (m->getRobotSizeInCells() * 2)), "coursefgrid.txt");
	cout << m->getRobotSizeInCells() << endl;

	stc = new STC(*m, make_pair(8, 2));
	stc->buildSpanningTree();
	stc->drawSpanningTree("way_points_path.png", m->getImageVector());

}

vector<string> InitEnvironment::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

string InitEnvironment::getMapImage(){
	return mapImg;
}
startLocation InitEnvironment::getStartLocation(){
	return startLocation;
}

double InitEnvironment::getRobotSize(){
	if (robotSize.first == robotSize.second){
		return robotSize.first;
	}
	return max(robotSize.first,robotSize.second);
}
double InitEnvironment::getMapResolution(){
	return MapResolution;
}

void InitEnvironment::start(){

}

wayPoint& InitEnvironment::getStartLocationAsStartWaypoint(){
	wayPoint* start = new wayPoint(startLocation.location.first, startLocation.location.second);
	cout << "start col: " << start->getX() << " " << "start row: " << start->getY() << endl;
	
	
	wayPoint* closest = new wayPoint(0,0);

	double mindistance = 99999;

	Node* n = stc->getNodeGraph().at(8).at(2);
	
	stack<wayPoint* > wayPointStack;
	wayPointStack.push(n->leftTopWayPoint);
	while (!wayPointStack.empty()){

		wayPoint* waypoint = wayPointStack.top();
		wayPointStack.pop();
		if (waypoint->getNext()->getX() == n->leftTopWayPoint->getX()
			&& waypoint->getNext()->getY() == n->leftTopWayPoint->getY()){
			break;
		}
		else{
			wayPointStack.push(waypoint->getNext());
		}
		if (waypoint != NULL)
		{
			cout << "col: " << waypoint->getX() << " " << "row: " << waypoint->getY() << endl;
			int distancex = pow((double)(waypoint->getX() - start->getX()),2.0);
			int distancey = pow((double)(waypoint->getY() - start->getY()), 2.0);

			double calcdistance = sqrt(distancex + distancey);
			if (calcdistance < mindistance){
				mindistance = calcdistance;
				closest->setX(waypoint->getX());
				closest->setY(waypoint->getY());
				start->setNextWayPoint(waypoint);
			}
		}


	}

	cout << "start col: " << start->getNext()->getX() << " " << "start row: " << start->getNext()->getY() << endl;
	cout << "closest col: " << closest->getX() << " " << "closest row: " << closest->getY() << endl;

	return *start;
}

InitEnvironment::~InitEnvironment()
{
}
