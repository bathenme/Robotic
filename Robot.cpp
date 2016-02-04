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


	decision = false;
	decided_direction_is_left = false;

	_pp->SetMotorEnable(true);
	_x=_pp->GetXPos();
	_y=_pp->GetYPos() ;
	_yaw=_pp->GetYaw();
	int i;
	for(i=0;i<200;i++)
	{
		_pc->Read();
	}

	_laserCount = _lp->GetCount();

}

// Methods
Robot::~Robot(){
delete _pp;
delete _pc;
delete _lp;
}

bool Robot::isBlocked(bool* is_blocked_from_right) {

	// Checking if the robot is blocked from the right
	if (!right_flank_clear())
	{

		if (!decision)
		{
			decided_direction_is_left = true;

			decision = true;
		}
	}
	// Checking if there is an obstacle from the left or forward
	else if (!left_flank_clear() || (*_lp)[333] < 0.3f)
	{
		if (!decision)
		{
			decided_direction_is_left = false;
			decision = true;
		}
	}
	// If the robot is not blocked changing the decision to false
	else
	{
		decision = false;
	}

	*is_blocked_from_right = decided_direction_is_left;
	return decision;
}

wayPoint* Robot::getDestWayPoint()
{
	return destWayPoint;
}
void Robot::setDestWayPoint(wayPoint* wp)
{
	destWayPoint = wp;
}
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
bool Robot::checkRadiusnew(float dis, double x,double y)
{


	double calcdistance (sqrtf((getXPosition() - x) * (getXPosition() - x)
			+ (getYPosition() - y) * (getYPosition() - y)));

	//double distancex = pow(x- getXPosition(),2.0);
	//double distancey = pow(y - getYPosition(), 2.0);

	//double calcdistance = sqrt(distancex + distancey);
	if(calcdistance < dis)
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
	//_x = (double)((_pp->GetXPos() * 100)/2.5) + (double)550/2;
//	_y = -(double)((_pp->GetYPos()* 100)/2.5) + (double)380/2;
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

	_x=_pp->GetXPos();
	return _x;
}

double Robot::getYPosition()
{
	_y=_pp->GetYPos();
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
bool Robot::right_flank_clear()
{
	for(int i = 333 + 50; i < 566; i+= 5)
	{
		// Checking if there is an obstacle in front of the robot
		if ((*_lp)[i] < 0.85 - i * 0.001)
	    {
	    	return false;
	    }
	}
	return true;
}

bool Robot::left_flank_clear()
{
	for(int i = 100; i < 333 - 50; i+= 5)
	{
		// Checking if there is an obstacle in front of the robot
	    if ((*_lp)[i] < 0.25 + i * 0.001)
	    {
	    	return false;
	    }
	}
	return true;
}

float Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

void Robot::updatePosition(double x, double y, double yaw)
{

	_x= 13.75*(x/550)-6.88;
	_y=-9.5*(y/380)+4.745;
	_yaw= 0.79;
//	_x = 2.17;
//	_y = -2.88;
	//_yaw = 20.0f * 3.14159f / 180.0f;
	_pp->SetOdometry(_x,_y,_yaw);
}
