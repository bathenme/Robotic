/*
 * Manager.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* plan) {
	_robot= robot;
	_plan = plan;
}
void Manager::run()
{
	Behavior* currBeh = _plan->getStart();
	_robot->read();
	if(!(currBeh->startCond()))
			return;
	while(currBeh)
	{
		_robot->read();
		cout << "changing behavior" << endl;
		while(!(currBeh->stopCond()))
		{
//			cout<<"x:"<<_robot->getXPosition()<<"y:"<<_robot->getYPosition()<<endl;
			currBeh->action();
			_robot->read();
		}
		_robot->setSpeed(0,0);
		return;
		currBeh = currBeh->getNext();
	}


}
Manager::~Manager() {
	// TODO Auto-generated destructor stub

}
