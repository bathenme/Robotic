/*
 * MoveForward.h
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"

class MoveForward: public Behavior {
public:
	MoveForward(Robot* robot,wayPoint* wp);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~MoveForward();
private:
	wayPoint* _wp;
};

#endif /* MOVEFORWARD_H_ */
