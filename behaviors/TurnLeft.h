/*
 * TurnLeft.h
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"
#include "../robot.h"
#include "../Map/wayPoint.h"

class TurnLeft: public Behavior {
private:
	double _angle;
	wayPoint* nextWay;
	double _direction;
public:
	double CalcAzimot(double x, double y);
	int AngleDirection(double angle, double yaw);
	TurnLeft(Robot* robot,wayPoint* wp);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~TurnLeft();
};

#endif /* TURNLEFT_H_ */
