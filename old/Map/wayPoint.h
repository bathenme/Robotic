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
	void setX(int x);
	void setY(int y);
	wayPoint* getNext();
	~wayPoint();
};

#endif
