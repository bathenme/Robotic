/*
 * wayPoint.h
 *
 *  Created on: Jan 25, 2016
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include <stdlib.h>
class wayPoint
{
private:
	int x;
	int y;
	wayPoint* next;

public:
	wayPoint(int x, int y);
	void setNextWayPoint(wayPoint* nextWayPoint);
	int getX();
	int getY();
	wayPoint* getNext();
	~wayPoint();
};

#endif /* WAYPOINT_H_ */
