/*
 * Robot.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port) :
	_pc(ip, port), _pp(&_pc), _lp(&_pc) {

	_pc = new PlayerCc::PlayerClient(ip,port);
	_pp = new PlayerCc::Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	_pp->SetOdometry(2.2,-2.875,0.34);

	int i;
	for(i=0;i<15;i++)
			{
				_pc->Read();
			}

	_oldX=
		_laserCount = _lp->GetCount();


}

void Robot::updatePosition(double x, double y, double yaw)
{
	_oldX = x;
	_oldY = y;
	_oldYaw = yaw;

}

void Robot::updateCurrPosition(double x, double y, double yaw)
{
	_x = x;
	_y = y;
	_yaw = yaw;
}

void Robot::setSpeed(float xSpeed, float ySpeed)
{
	_pp->SetSpeed(xSpeed, ySpeed);
}
bool Robot::freeInFront(float distance)
{
	int i;
	for(i=300;i<400;i+=5)
		if(_lp[i] < distance)
			return false;

	return true;
}

bool Robot::checkRange(int nStart, int nEnd)
{
	bool is_Good = true;

	for (int index = nStart; (index <= nEnd) && (is_Good); index++)
	{
		is_Good = (this->getLaserDistance(index) > DISTANCE_TOLERANCE);
	}

	return (is_Good);
}

float Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);

}



double Robot::getOldYawPosition()
{
 return _oldYaw;
}
double Robot::getOldYPosition()
{
	return _oldY;
}
double Robot::getOldXPosition()
{
 return _oldX;
}
LaserProxy* Robot::getLaser()
{
	return _lp;
}
double Robot::getYawPosition()
{
	return _yaw;
}
double Robot::getXPosition()
{
	return _x ;
}

double Robot::getYPosition()
{
	return _y ;
}



Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
