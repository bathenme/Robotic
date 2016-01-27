/*
 * main.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */
#include "Configuration/ConfigManager.h"
#include "Plans/ObstacleAvoidPlan.h"
#include "Robot.h"
#include "Manager.h"
#include "Map/Map.h"
#include "STCAlg/STC.h"
#include "InitEnvironment.h"
const char* PARAMETERS = "parameters.txt";
int main()
{
	InitEnvironment init = InitEnvironment(PARAMETERS);
	wayPoint wp =  init.getStartLocationAsStartWaypoint();

	Robot robot("localhost", 6665);

	ObstacleAvoidPlan pln(&robot,wp);
	Manager manager(&robot, &pln);
	manager.run();
	return 0;
}
