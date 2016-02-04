/*
 * MoveForward.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "MoveForward.h"

MoveForward::MoveForward(Robot* robot):Behavior(robot) {

	// TODO Auto-generated constructor stub

}
bool MoveForward::startCond()
{
	cout<<"start con MOVEFOR"<<endl;
	return _robot->freeInFront(0.3);
}
bool MoveForward::stopCond()
{
	cout<<"stop con movefor"<<endl;
	cout<<"wp x:"<<_robot->getDestWayPoint()->getNext()->getXNew()<<"wp y:"<<_robot->getDestWayPoint()->getNext()->getYNew()<<endl;

	if((_robot->checkRadiusnew(0.3,_robot->getDestWayPoint()->getNext()->getXNew(),_robot->getDestWayPoint()->getNext()->getYNew())||(!_robot->freeInFront(0.3))))
	{
		cout<<"iffff"<<endl;
	//	_robot->setSpeed(0.0,0.0);
		//_robot->setDestWayPoint(_robot->getDestWayPoint()->getNext());
		return true;
}
	return false;
}
void MoveForward::action()
{
    _robot->setSpeed(1.0f,0.0f); // simply drive straight.
	cout<<"MOVEFOR"<<endl;
}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}
