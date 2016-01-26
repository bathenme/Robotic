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


int main()
{
	// Read the configuration file
	ConfigManager::ReadParameters();

	// Read and inflate map
	const char* FILEPATH = "roboticLabMap.png";
	float robotsize = ConfigManager::GetRobotWidth;
	float mapres =ConfigManager::GetMapResolution;
	Map m = Map(mapres/10,robotsize/10,FILEPATH);
	m.loadMap();
	m.buildGrid(m.getRobotSizeInCells(), m.GetFineGrid());
	m.buildGrid((m.getRobotSizeInCells() * 2), m.GetCoarseGrid());
	m.printGrid(m.GetFineGrid(),(m.getMapHeight()/m.getRobotSizeInCells()),(m.getMapWidth()/m.getRobotSizeInCells()),"finegrid.txt");
	m.printGrid(m.GetCoarseGrid(), (m.getMapHeight() / (m.getRobotSizeInCells() * 2)), (m.getMapWidth() / (m.getRobotSizeInCells()*2)),"coursefgrid.txt");
	cout << m.getRobotSizeInCells() << endl;

	//stc
	STC stc = STC(m, std::make_pair(8, 2));
	stc.buildSpanningTree();
	stc.printNodes();
	stc.drawSpanningTree("temp.pmg", m.getImageVector());


	Robot robot("localhost", 6665);
	ObstacleAvoidPlan pln(&robot,&wp);
	Manager manager(&robot, &pln);
	manager.run();
	return 0;
}
