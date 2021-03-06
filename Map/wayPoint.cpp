#include "wayPoint.h"


wayPoint::wayPoint(double x, double y) :x(x), y(y), next(NULL){

}

void wayPoint::setNextWayPoint(wayPoint* nextWayPoint){
	next = nextWayPoint;
}

double wayPoint::getX(){
	return x;
}

double wayPoint::getY(){
	return y;
}

double wayPoint::getXNew()
{
	return 13.75*(x/550)-6.875;
}
double wayPoint::getYNew()
{
	return -9.5*(y/380)+4.75;
}
wayPoint* wayPoint::getNext(){
	return next;
}
void wayPoint::setX(double xx){
	x = xx;
}
void wayPoint::setY(double yy){
	y = yy;
}

wayPoint::~wayPoint()
{

}
