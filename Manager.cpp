/*
 * Manager.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* plan) {
	// TODO Auto-generated constructor stub
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
		while(!(currBeh->stopCond()))
		{
			currBeh->action();
			_robot->read();
		}
		currBeh = currBeh->getNext();
	}


}
Manager::~Manager() {
	// TODO Auto-generated destructor stub

}
