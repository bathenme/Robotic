/*
 * robot.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "robot.h"

Robot::Robot(char* ip, int port){
	_pc = new PlayerCc::PlayerClient(ip,port);
	_pp = new PlayerCc::Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	_x=_pp->GetXPos();
	_y=_pp->GetYPos() ;
	_yaw=_pp->GetYaw();
	int i;
	for(i=0;i<15;i++)
	{
		_pc->Read();
	}
	//TOFIX
	_laserCount = _lp->GetCount();

}

// Methods


bool Robot::checkRadius(float dis, Position pos)
{

	double distancex = pow(pos.first- getXPosition(),2.0);
	double distancey = pow(pos.second - getYPosition(), 2.0);

	double calcdistance = sqrt(distancex + distancey);
	if(calcdistance <= dis)
	{
		return true;
	}
	return false;
}

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
	_x = (double)((_pp->GetXPos() * 100)/2.5) + (double)550/2;
	_y = -(double)((_pp->GetYPos()* 100)/2.5) + (double)380/2;
	_pc->Read();
}

double Robot::CalcAzimot(double x, double y)
{
	double angle;
	double deltaX = x- _pp->GetXPos();
	double deltaY = y - _pp->GetYPos();


	angle = atan2(deltaY, deltaX);

	return angle;
}
int Robot::AngleDirection(double angle)
{

	double res = angle - _pp->GetYaw();
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



LaserProxy* Robot::getLaser()
{
	return _lp;
}
double Robot::getYawPosition()
{
	return _pp->GetYaw();
}
double Robot::getXPosition()
{
	return _x;
}

double Robot::getYPosition()
{
	return _y;
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
	//_x = x ;

	//_y= y;
	//_yaw =yaw;
	//_pp->SetOdometry(x,y, yaw);
	_pp->SetOdometry(2.5,-3.05,0.05);


}
