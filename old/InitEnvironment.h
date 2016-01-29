/*
 * InitEnvironment.h
 *
 *  Created on: Jan 29, 2016
 *      Author: colman
 */

#ifndef INITENVIRONMENT_H_
#define INITENVIRONMENT_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include "Map/wayPoint.h"
#include "STCAlg/STC.h"
#include "Map/Map.h"
#include "robot.h"


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
	InitEnvironment(const char* parametersFile, Robot* robot);
	void setRobot(Robot* robot);
	const char* getMapImage();
	startLocation getStartLocation();
	Position getStartXY();
	double getStartYaw();
	double getRobotSize();
	double getMapResolution();
	wayPoint& getStartLocationAsStartWaypoint();
	void start();
	~InitEnvironment();

private:
	Map* m;
	STC* stc;
	const char* mapImg;
	Position startXY;
	double startYaw;
	startLocation robotStartLocation;
	robotSize sizeRobot;
	double MapResolution;
	vector<string> split(string str, char delimiter);
};



#endif /* INITENVIRONMENT_H_ */
