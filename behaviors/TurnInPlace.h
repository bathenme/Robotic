/*
 * TurnInPlace.h
 */

#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_
#include "Behavior.h"
#include "../robot.h"
#include "../Configuration/Constants.h"
#include "../Map/wayPoint.h"

#include <math.h>

class TurnInPlace: public Behavior {
private:
	double _angle;
	double _direction;
	wayPoint* nextWay ;


public:
	double CalcAzimot(double x, double y);
	int AngleDirection(double angle, double yaw);
	TurnInPlace(Robot* robot,wayPoint* wp);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~TurnInPlace();
};

#endif /* TURNINPLACE_H_ */
