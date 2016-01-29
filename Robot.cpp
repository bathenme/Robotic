/*
 * robot.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "robot.h"
#include "math.h"

Robot::Robot(char* ip, int port){
	_pc = new PlayerCc::PlayerClient(ip,port);
	_pp = new PlayerCc::Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);


	int i;
	for(i=0;i<15;i++)
	{
		_pc->Read();
	}
	//TOFIX
	_laserCount = _lp->GetCount();

}

// Methods

bool Robot::freeInFront(float distance)
{
	int i;
	for(i=300;i<400;i+=5){
		if((*_lp)[i] < distance)
		{
			return false;
		}
	}

	return true;
}

void Robot::read()
{
	_pc->Read();


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


int Robot::getLaserCount()
{
	return _laserCount;
}


void Robot::setSpeed(float speed, float angularSpeed)
{
	_pp->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

void Robot::updatePosition(double x, double y, double yaw)
{
	_x = x;

	_y= y;
	_yaw =yaw;
	_pp->SetOdometry(x,y, yaw);

}
