/*
 * Behavior.h
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include "../robot.h"
#include "../Map/wayPoint.h"
#include <iostream>

using namespace std;
class Behavior {
protected:
	Robot* _robot;
	Behavior** _next;
	int _sizeOfNext;
public:
	Behavior(Robot* robot,wayPoint* wp);
	virtual bool startCond()=0;
	virtual bool stopCond()=0;
	virtual void action() = 0;
	bool addNext(Behavior* beh);
	Behavior* getNext();
	virtual ~Behavior();
};

#endif /* BEHAVIOR_H_ */
