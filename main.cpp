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

	InitEnvironment init = InitEnvironment(PARAMETERS, robot);
	wayPoint wp =  init.getStartLocationAsStartWaypoint();
	PlnObstacleAvoid pln(robot);
	Manager manager(robot, &pln);
	manager.run();
	return 0;
}
