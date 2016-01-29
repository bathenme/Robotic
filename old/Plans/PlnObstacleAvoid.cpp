/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "PlnObstacleAvoid.h"
#include "../behaviors/MoveForward.h"
PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) {
	// TODO Auto-generated constructor stub
	//Creating behaviors
	_behaviors[0] = new MoveForward(robot);
	_behaviors[1] = new MoveForward(robot);
	_behaviors[2] = new MoveForward(robot);

	//Connecting behaviors
	_behaviors[0]->addNext(_behaviors[1]);
	_behaviors[0]->addNext(_behaviors[2]);

	_behaviors[1]->addNext(_behaviors[0]);
	_behaviors[1]->addNext(_behaviors[2]);


	_behaviors[2]->addNext(_behaviors[0]);

	_start = _behaviors[0];

}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	int i;
	for(i=0;i<3;i++)
			delete []_behaviors[i];
}
