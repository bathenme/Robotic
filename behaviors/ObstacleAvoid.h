
#ifndef ACTIONOBSTACLE_H_
#define ACTIONOBSTACLE_H_

#include "Behavior.h"
#include <ctime>

#define DRIVE_AWAY_TIME_SECONDS 2

class ObstacleAvoid: public Behavior {
private:
	bool obstacle_from_right;
	clock_t drive_away_start_time;
	bool drive_away;
public:
	ObstacleAvoid(Robot* robot);
	virtual ~ObstacleAvoid(){}
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* ACTIONOBSTACLE_H_ */
