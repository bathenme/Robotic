/*
 * GotoWaypoint.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#include "GotoWaypoint.h"



GotoWaypoint::GotoWaypoint(Robot* robot):Behavior(robot) {

	_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());
	//_direction = dtor(_robot->AngleDirection(_angle));
}
bool GotoWaypoint::startCond()
{
	cout<<"start con way"<<endl;
	return true;
}
bool GotoWaypoint::stopCond()
{
	cout<<"stop con way"<<endl;
_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());

if (fabs(_angle - _robot->getYawPosition()) <= 0.1f) // it is less than 1 degree diffrence.
{
	_robot->setSpeed(0.0,0.0); // stop moving for now.
	return true;
}

return false;
}

double GotoWaypoint::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = _robot->getDestWayPoint()->getNext()->getXNew() - x;
	double deltaY = _robot->getDestWayPoint()->getNext()->getYNew()  - y;


	angle = atan2(deltaY, deltaX);

	return angle;
}

void GotoWaypoint::action()
{

	_angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());

	cout<<"angle:"<<_angle<<"  "<<"yaw"<<_robot->getYawPosition()<<endl;
	cout<<"wp:"<<_robot->getDestWayPoint()->getNext()->getXNew()<<"y:"<<_robot->getDestWayPoint()->getNext()->getYNew()<<endl;
		// rotate slowly to target angle
	if (_robot->getYawPosition() > _angle)
	{
		cout<<"minus"<<endl;
	    _robot->setSpeed(0.0f, -0.3f);
	}
	else
	{
		cout<<"plus"<<endl;
		_robot->setSpeed(0.0f, 0.3f);
	}
}


GotoWaypoint::~GotoWaypoint() {

}

