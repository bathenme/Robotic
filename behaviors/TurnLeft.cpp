/*
 * TurnLeft.cpp
 */

#include "TurnLeft.h"
#include "../Configuration/Constants.h"


TurnLeft::TurnLeft(Robot* robot): Behavior(robot) {
}

bool TurnLeft::startCond()
{
	_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());
	_direction = dtor(AngleDirection(_angle, _robot->getYawPosition()));
	return true;

}
double TurnLeft::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = nextWay->getX() - (int)x;
	double deltaY = nextWay->getY() - (int)y;


	angle = atan2(deltaY, deltaX);

	//return angle;
	return PAI;
}
int TurnLeft::AngleDirection(double angle, double yaw)
{

	double res = angle - yaw;
		res += (res > (PAI))? -(2 *PAI): (res<-PAI) ? (2*PAI):0;
		if(res > 0)
		{
			return 10;
		}
		else
		{
			return -10;
		}
}
void TurnLeft::action()
{
	_robot->setSpeed(TURN_SPEED, _direction);


}

bool TurnLeft::stopCond()
{
	// check if we got to the way point
	if (abs(_robot->getYawPosition() - (_angle)) < 0.03)
	{
		// we need to change direction
		_robot->setSpeed(0,0.0);
		return true;
	}

	// we didnt get to the waypoint yet
	return false;
}

TurnLeft::~TurnLeft() {
}
