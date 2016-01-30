#ifndef ROBOT_H_
#define ROBOT_H_
#include<string.h>
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <vector>
#include "Configuration/Constants.h"
#include <cmath>

using namespace PlayerCc;
using namespace std;
typedef pair<double, double> Position;
class Robot {
private:
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	double _x;
	double _y;
	double _yaw;
	int _laserCount;

public:
	double CalcAzimot(double x, double y);
	int AngleDirection(double angle);
	bool freeInFront(float distance);
	Robot(char* ip, int port);
	std::vector<vector<int> >  resolutionMapAfterBlow;
	std::vector<vector<int> >  resolutionMapBeforeBlow;
	int** _mapMatrixBeforeBlow;
	const char* mapName;
	double robotWidth;
	double robotLengt;
	double mapResolution;
	double gridWidth;
	double gridResolution;
	void read();
	void setSpeed(float speed, float angularSpeed);
	bool checkRadius(float dis, Position pos);
	float getLaserDistance(int index);
	double getXPosition();
	double getYPosition();
	double getYawPosition();
	int getLaserCount();
	LaserProxy* getLaser();
	void updatePosition(double x, double y, double yaw);
};

#endif /* ROBOT_H_ */
