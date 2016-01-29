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
#include <cmath>


using namespace std;

typedef pair<int, int> Position;
typedef pair<float, float> robotSize;
struct startLocation {
	Position location;
	float yaw;
};

class InitEnvironment
{
public:
	InitEnvironment(const char* parametersFile);
	char* getMapImage();
	startLocation getStartLocation();
	Position getStartXY();
	float getStartYaw();
	float getRobotSize();
	float getMapResolution();
	wayPoint& getStartLocationAsStartWaypoint();
	void start();
	~InitEnvironment();

private:
	Map* m;
	STC* stc;
	char* mapImg;
	Position startXY;
	float startYaw;
	startLocation robotStartLocation;
	robotSize sizeRobot;
	float MapResolution;
	vector<string> split(string str, char delimiter);
};



#endif /* INITENVIRONMENT_H_ */
