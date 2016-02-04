/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "PlnObstacleAvoid.h"
#include "../behaviors/ObstacleAvoid.h"
#include "../behaviors/GotoWaypoint.h"
#include "../behaviors/MoveForward.h"
#include "../behaviors/WaypointSelectionBehaviour.h"
PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) {


	//Creating behaviors
	_behaviors[0] = new WaypointSelectionBehaviour(robot);
	_behaviors[1] = new GotoWaypoint(robot);
	_behaviors[2] = new MoveForward(robot);
	_behaviors[3] = new ObstacleAvoid(robot);
	//Connecting behaviors
	_behaviors[0]->addNext(_behaviors[1]);
	_behaviors[1]->addNext(_behaviors[2]);
	_behaviors[1]->addNext(_behaviors[3]);
	_behaviors[2]->addNext(_behaviors[0]);
	_behaviors[2]->addNext(_behaviors[3]);
	_behaviors[3]->addNext(_behaviors[0]);
	_behaviors[3]->addNext(_behaviors[1]);




	_start = _behaviors[1];

}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	int i;
	for(i=0;i<4;i++)
			delete []_behaviors[i];
}
