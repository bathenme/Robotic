/*
 * GotoWaypoint.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#include "GotoWaypoint.h"



GotoWaypoint::GotoWaypoint(Robot* robot,wayPoint* wp):Behavior(robot,wp) {
	_wp = wp;
}
bool GotoWaypoint::startCond()
{
	return true;
}
bool GotoWaypoint::stopCond()
{
	if(_robot->checkRadius(3.0, std::make_pair(_wp->getNext()->getX() ,_wp->getNext()->getY() ))){
		_wp=_wp->getNext();
		cout << "stopping!" << endl;
		return true;
	}
	return false;
}

double GotoWaypoint::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = _wp->getNext()->getX() - x;
	double deltaY = _wp->getNext()->getY()  - y;


	angle = atan2(deltaY, deltaX);

	return angle;
}

void GotoWaypoint::action()
{
	double _angle = CalcAzimot(_robot->getXPosition(), _robot->getYPosition());
	double _deltaAngle = 0;

	_deltaAngle = fabs(_angle) - fabs(_robot->getYawPosition());

	double _angleSpeed = 0.0f;
	double _forwardSpeed = 0.5f;

	cout << "going from: " << _robot->getXPosition() <<"," << _robot->getYPosition();
	cout << "to waypoint: " << _wp->getNext()->getX()  << "," <<  _wp->getNext()->getY()  << endl;
	cout << "angle: " << _angle << "delta angle: " << _deltaAngle << endl;
	cout<<"yaw:      "<<_robot->getYawPosition()<<endl;

	if (fabs(_deltaAngle) > 0.1f){
		_forwardSpeed = 0.0f;
		if (_deltaAngle > 0.0f){
			_angleSpeed = fmin(-0.5f, -0.05f * fabs(_deltaAngle));
			cout << "turning minus" << endl;
		}
		else{
			_angleSpeed = fmin(0.5f, 0.05f * fabs(_deltaAngle));
			cout << "turning plus" << endl;
		}
	}
	cout << "going forward" << endl;
	_robot->setSpeed(_forwardSpeed, _angleSpeed);
}

GotoWaypoint::~GotoWaypoint() {

}

