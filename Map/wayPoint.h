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
	double x;
	double y;
	wayPoint* next;

public:
	wayPoint(double x, double y);
	void setNextWayPoint(wayPoint* nextWayPoint);
	double getX();
	double getY();
	double getXNew();
		double getYNew();
	void setX(double x);
	void setY(double y);
	wayPoint* getNext();
	~wayPoint();
};


#endif /* WAYPOINT_H_ */
