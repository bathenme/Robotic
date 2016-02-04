

#ifndef ACTIONSELECTWAYPOINT_H_
#define ACTIONSELECTWAYPOINT_H_

#include "Behavior.h"
#include "../Map/wayPoint.h"

class WaypointSelectionBehaviour: public Behavior {
private:
	bool isWaypointSet;

public:
	WaypointSelectionBehaviour(Robot* robot);
	virtual ~WaypointSelectionBehaviour(){};
	bool startCond();
	bool stopCond();
	void action();

};

#endif /* ACTIONSELECTWAYPOINT_H_ */
