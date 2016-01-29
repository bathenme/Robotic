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
	//TOFIX
	_pp->SetOdometry(2.2,-2.875,0.34);

	int i;
	for(i=0;i<15;i++)
	{
		_pc->Read();
	}
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
	_x = (double)((_pp->GetXPos() * 100)/gridResolution) + (double)gridWidth/2;
	_y = -(double)((_pp->GetYPos()* 100)/gridResolution) + (double)gridHeight/2;
	_yaw = _pp->GetYaw();


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
