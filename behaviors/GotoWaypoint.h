/*
 * GotoWaypoint.h
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#ifndef GOTOWAYPOINT_H_
#define GOTOWAYPOINT_H_

#include "Behavior.h"

class GotoWaypoint: public Behavior {
public:
	GotoWaypoint(Robot* robot);
	virtual ~GotoWaypoint();
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	double CalcAzimot(double x, double y);

private:
	double _direction;
	double _angle;

};

#endif /* GOTOWAYPOINT_H_ */
