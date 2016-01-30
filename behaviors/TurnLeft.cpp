/*
 * TurnLeft.cpp
 */

#include "TurnLeft.h"
#include "../Configuration/Constants.h"


TurnLeft::TurnLeft(Robot* robot,wayPoint* wp): Behavior(robot,wp) {
	nextWay=wp;

}

bool TurnLeft::startCond()
{
	_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());

	//	_direction = dtor(AngleDirection(_angle, _robot->getYawPosition()));

	return true;

}
double TurnLeft::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = nextWay->getX() - (int)x;
	double deltaY = nextWay->getY() - (int)y;


	angle = atan2(deltaY, deltaX);

	//return angle;
	return angle;
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

	// rotate slowly to target angle
	if (_robot->getYawPosition() > _angle)
	{
	    _robot->setSpeed(0.0f, -0.15f);
	}
	else
	{
		_robot->setSpeed(0.0f, 0.15f);
	}

}

bool TurnLeft::stopCond()
{
	cout<<fabs(_robot->getYawPosition() - (_angle))<<"stopcon turn left"<<endl;
	// check if we got to the way point
	if (fabs( (_angle)- _robot->getYawPosition()) <= 0.01f)
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
