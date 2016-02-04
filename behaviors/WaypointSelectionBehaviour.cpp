
#include "WaypointSelectionBehaviour.h"

WaypointSelectionBehaviour::WaypointSelectionBehaviour(Robot* robot) : Behavior(robot){
	// TODO Auto-generated constructor stub
	isWaypointSet = false;
}

bool WaypointSelectionBehaviour::startCond()
{
	double x= _robot->getDestWayPoint()->getNext()->getXNew();
	double y = _robot->getDestWayPoint()->getNext()->getYNew();
	// check if the robot is near our current waypoint.
    if (_robot->checkRadiusnew(0.3,x,y))
    {
    	isWaypointSet = false; // do it before we select a waypoint. so action will be called.
    	cout << "Started Action_SelectWaypoint" << endl;
    	return true;
    }

    // the robot is not close to the current waypoint. cant switch waypoints.
    return false;
}
bool WaypointSelectionBehaviour::stopCond()
{
	// if the waypoint was not set, stay in the behaviour.
	// basicly im just making sure the action func ran atleast once.
   return isWaypointSet;
}
void WaypointSelectionBehaviour::action()
{
	// if you reached your current waypoint, set a new one!
	double x= _robot->getDestWayPoint()->getNext()->getXNew();
	double y = _robot->getDestWayPoint()->getNext()->getYNew();
	// check if the robot is near our current waypoint.
    if (_robot->checkRadiusnew(0.3,x,y))
    {
    	_robot->setDestWayPoint(_robot->getDestWayPoint()->getNext());
	}


	isWaypointSet = true;
}

