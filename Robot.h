/*
 * Robot.h
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Configuration/Constants.h"
using namespace PlayerCc;

class Robot {
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
public:
	Robot(char* ip, int port);
	void Read(){_pc.Read();}
	void setSpeed(float xSpeed, float ySpeed);
	bool freeInFront(float distance);
	bool checkRange(int nStart, int nEnd);
	float getLaserDistance(int index);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
