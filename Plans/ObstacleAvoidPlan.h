/*
 * ObstacleAvoidPlan.h
 *
 *  Created on: Jun 21, 2015
 *      Author: user
 */

#ifndef OBSTACLEAVOIDPLAN_H_
#define OBSTACLEAVOIDPLAN_H_

#include "Plan.h"

class ObstacleAvoidPlan: public Plan {
	Behavior* _beh[4];

public:
	ObstacleAvoidPlan(Robot* robot, WaypointsManager* wpm);
	Behavior* getStartPoint();
	virtual ~ObstacleAvoidPlan();
};

#endif /* OBSTACLEAVOIDPLAN_H_ */


