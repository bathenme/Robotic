/*
 * GoToWayPoint.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef GOTOWAYPOINT_H_
#define GOTOWAYPOINT_H_

#include "Behavior.h"
#include "../Map/wayPoint.h"
class GoToWayPoint: public Behavior {
public:
	GoToWayPoint(Robot* robot, wayPoint Wpm);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~GoToWayPoint();

private:
	wayPoint _wpm;
	bool isRight;
	double diffrence;

};

#endif /* GOTOWAYPOINT_H_ */
