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
	return _robot->freeInFront(1.0);
}
bool MoveForward::stopCond()
{
	return !(_robot->freeInFront(0.8));
}
void MoveForward::action()
{
	_robot->setSpeed(0.5,0.2);
	cout<<"MOVEFOR"<<endl;
}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}
