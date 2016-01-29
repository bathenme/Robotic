

#include "ObstacleAvoidPlan.h"
#include "../behaviors/ForwardBehaviour.h"
#include "../behaviors/GoToWayPoint.h"

ObstacleAvoidPlan::ObstacleAvoidPlan(Robot* robot, wayPoint wpm) : Plan(robot){

	//Creating Behaviors
	_beh[0] = new GoToWayPoint(robot, wpm); // first thing to be done! EVEN if start cond doesnt return true.
		_beh[1] = new ForwardBehaviour(robot);
		//Connecting Behaviors
		_beh[0]->addNext(_beh[1]); // first select a waypoint and than move to it.
		_beh[1]->addNext(_beh[0]);
		_start = _beh[0];
}

Behavior* ObstacleAvoidPlan::getStartPoint(){
	return _start;
}

ObstacleAvoidPlan::~ObstacleAvoidPlan() {

	for(int i = 0; i < 2; i++)
		delete _beh[i];
}
