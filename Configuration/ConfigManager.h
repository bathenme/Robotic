/*
 * ConfigManager.h
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_
#define DIRECTION_VECTOR_SIZE 8

#include <iostream>
#include <fstream>
#include <string.h>
#include "../Location.h"

class Location;

class ConfigManager {
public:
	ConfigManager();
	virtual ~ConfigManager();
	static void ReadParameters();
	static std::string GetMapUrl();
	static Location* GetStartLocationMapResolution();
	static Location* GetStartLocationRealWorldResolution();
	static int GetstartLocationYaw();
	static int GetRobotWidth();
	static int GetRobotHeight();
	double GetMapResolution();
private:
	static std::string mapUrl;
	static Location* startLocation;
	static int startLocationYaw;
	static int robotWidth;
	static int robotHeight;
	static double mapResolution;

};
#endif /* CONFIGMANAGER_H_ */
