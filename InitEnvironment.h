#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "wayPoint.h"
#include "STC.h"
#include "Map.h"
#include <cmath>


using namespace std;

typedef pair<int, int> Position;
typedef pair<double, double> robotSize;
struct startLocation {
	Position location;
	double yaw;
};

class InitEnvironment
{
public:
	InitEnvironment(const char* parametersFile);
	string getMapImage();
	startLocation getStartLocation();
	double getRobotSize();
	double getMapResolution();
	wayPoint& getStartLocationAsStartWaypoint();
	void start();
	~InitEnvironment();

private:
	Map* m;
	STC* stc;
	string mapImg;
	startLocation startLocation;
	robotSize robotSize;
	double MapResolution;
	vector<string> split(string str, char delimiter);
};

