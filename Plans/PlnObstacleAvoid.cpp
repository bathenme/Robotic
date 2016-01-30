/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "PlnObstacleAvoid.h"
#include "../behaviors/MoveForward.h"
#include "../behaviors/GotoWaypoint.h"
PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot,wayPoint* wp) {
	//Creating behaviors
	_behaviors[0] = new GotoWaypoint(robot,wp);

	//Connecting behaviors
	_behaviors[0]->addNext(_behaviors[0]);

	_start = _behaviors[0];

}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	int i;
	for(i=0;i<2;i++)
			delete []_behaviors[i];
}
