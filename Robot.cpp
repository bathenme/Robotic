/*
 * Robot.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port) :
	_pc(ip, port), _pp(&_pc), _lp(&_pc) {
	// TODO Auto-generated constructor stub
	_pp.SetMotorEnable(true);

}
void Robot::setSpeed(float xSpeed, float ySpeed)
{
	_pp.SetSpeed(xSpeed, ySpeed);
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
Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
