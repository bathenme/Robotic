/*
 * PlnObstacleAvoid.h
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "Plan.h"
#include "../robot.h"
class PlnObstacleAvoid: public Plan {
	Behavior* _behaviors[3];
public:
	PlnObstacleAvoid(Robot* robot,wayPoint* wp);
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
