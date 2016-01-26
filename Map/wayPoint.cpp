#include "wayPoint.h"


wayPoint::wayPoint(int x, int y) :x(x), y(y), next(NULL){

}

void wayPoint::setNextWayPoint(wayPoint* nextWayPoint){
	next = nextWayPoint;
}

int wayPoint::getX(){
	return x;
}

int wayPoint::getY(){
	return y;
}
wayPoint* wayPoint::getNext(){
	return next;
}
wayPoint::~wayPoint()
{

}