/*
 * MoveForward.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "MoveForward.h"

MoveForward::MoveForward(Robot* robot,wayPoint* wp):Behavior(robot,wp) {
	_wp = wp;
	// TODO Auto-generated constructor stub

}
bool MoveForward::startCond()
{
	cout<<"start con MOVEFOR"<<endl;
	return _robot->freeInFront(1.0);
}
bool MoveForward::stopCond()
{
	cout<<"stop con movefor"<<endl;
	cout<<"wp:"<<_wp->getX()<<"y:"<<_wp->getY()<<endl;

	if((_robot->getXPosition()==_wp->getX())&&(_robot->getYPosition()==_wp->getY()))
		{
			_wp=_wp->getNext();
			_robot->setSpeed(0.0,0.0);
			return true;
		}
	return false;
}
void MoveForward::action()
{
    _robot->setSpeed(0.2f,0.0f); // simply drive straight.
	cout<<"MOVEFOR"<<endl;
}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}
