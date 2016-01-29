
#ifndef ACTIONDRIVE_H_
#define ACTIONDRIVE_H_

#include "Behavior.h"

class ForwardBehaviour: public Behavior {
public:
	ForwardBehaviour(Robot* robot);
	virtual ~ForwardBehaviour(){}
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONDRIVE_H_ */
