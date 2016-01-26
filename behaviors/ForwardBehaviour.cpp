
#include "ForwardBehaviour.h"
#include <math.h>

ForwardBehaviour::ForwardBehaviour(Robot* robot) : Behavior(robot){
	// TODO Auto-generated constructor stub

}

bool ForwardBehaviour::startCond()
{
	return _robot->freeInFront(1.0);
}
bool ForwardBehaviour::stopCond()
{
	return !(_robot->freeInFront(0.8));
}
void ForwardBehaviour::action()
{
    // set positive speed in target direction
    _robot->setSpeed(1.0f,0.0f); // simply drive straight.
}
