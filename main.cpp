/*
 * main.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */
#include "Plans/PlnObstacleAvoid.h"
#include "robot.h"
#include "Manager.h"
#include "Map/Map.h"
#include "STCAlg/STC.h"
#include "InitEnvironment.h"
const char* PARAMETERS = "parameters.txt";
int main()
{
	Robot* robot = new Robot("localhost", 6665);
	cout<<"start main"<<endl;
	InitEnvironment init = InitEnvironment(PARAMETERS);
	robot->updatePosition(init.getStartLocation().location.second,init.getStartLocation().location.first,init.getStartLocation().yaw);

	cout<<"start wp"<<endl;
	wayPoint wp =  init.getStartLocationAsStartWaypoint();
	wayPoint* wpn =wp.getNext();
	cout<<"start wp"<<endl;
	robot->setDestWayPoint(wpn);
	cout<<"start wp"<<endl;
	PlnObstacleAvoid pln(robot);
	cout<<"start manager"<<endl;
	Manager manager(robot, &pln);
	cout<<"run"<<endl;
	manager.run();
	return 0;
}
