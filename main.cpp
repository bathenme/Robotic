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
	cout << "maor" << init.getStartLocation().location.first << " " << init.getStartLocation().location.second << endl;
	robot->updatePosition(init.getStartLocation().location.first,init.getStartLocation().location.second,init.getStartLocation().yaw);

	cout<<"start wp"<<endl;
	wayPoint wp =  init.getStartLocationAsStartWaypoint();
	PlnObstacleAvoid pln(robot,&wp);
	Manager manager(robot, &pln);
	manager.run();
	return 0;
}
