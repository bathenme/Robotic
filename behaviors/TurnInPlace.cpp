/*
 * TurnInPlace.cpp
 */

#include "TurnInPlace.h"
#include "Behavior.h"

TurnInPlace::TurnInPlace(Robot* robot): Behavior(robot) {

}

bool TurnInPlace::startCond()
{
	_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());
	_direction = dtor(AngleDirection(_angle, _robot->getYawPosition()));
	return true;
}

void TurnInPlace::action()
{
	_robot->setSpeed(0.2, _direction);
	cout<<"INPLACE"<<endl;
}

double TurnInPlace::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = nextWay->getX()- (int)x;
	double deltaY = nextWay->getY() - (int)y;


	angle = atan2(deltaY, deltaX);

	return -angle;
}
int TurnInPlace::AngleDirection(double angle, double yaw)
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
bool TurnInPlace::stopCond()
{
	// check if we got to the way point
	if (abs(_robot->getYawPosition() - _angle) < 0.05)
	{
		// we need to change direction
		_robot->setSpeed(0,0.0);
		return true;
	}

		 //we didnt get to the waypoint yet
		return false;
}

TurnInPlace::~TurnInPlace() {
}
