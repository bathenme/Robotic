#ifndef ROBOT_H_
#define ROBOT_H_
#include <string.h>
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <vector>
#include "Configuration/Constants.h"
#include <cmath>
#include "Map/wayPoint.h"

using namespace PlayerCc;
using namespace std;
typedef pair<double, double> Position;
class Robot {
private:
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	bool decision;
	bool decided_direction_is_left;
	double _x;
	double _y;
	double _yaw;
	int _laserCount;
	wayPoint* destWayPoint;

public:
	bool isBlocked(bool* is_blocked_from_right);
	bool right_flank_clear();
	bool left_flank_clear();
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
	bool checkRadiusnew(float dis ,double x,double y);
	float getLaserDistance(int index);
	double getXPosition();
	double getYPosition();
	double getYawPosition();
	wayPoint* getDestWayPoint();
	void setDestWayPoint(wayPoint* wp);
	int getLaserCount();
	LaserProxy* getLaser();
	void updatePosition(double x, double y, double yaw);
	~Robot();
};

#endif /* ROBOT_H_ */
