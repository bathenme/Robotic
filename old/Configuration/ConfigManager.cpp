/*
 * ConfigManager.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "ConfigManager.h"
#include "Constants.h"
using namespace std;

string ConfigManager::mapUrl;
Location* ConfigManager::startLocation;
int ConfigManager::startLocationYaw;
int ConfigManager::robotWidth;
int ConfigManager::robotHeight;
double ConfigManager::mapResolution;

ConfigManager::ConfigManager() {
}

ConfigManager::~ConfigManager() {
}

void ConfigManager::ReadParameters()
{
	  string line;
	  ifstream myfile ("Configuration/parameters.txt");
	  if (myfile.is_open())
	  {
		  string parameter;
		  string value;
		  string delimiter = ":";
		  int pos;

		  while ( getline (myfile,line) ) {

	    	pos = line.find(delimiter);
	    	parameter = line.substr(0, pos);
	    	value = line.substr(pos + 2, line.length() - pos);

	    	if (parameter == "map")
			{
	    		mapUrl = value;
			}
	    	else if (parameter == "startLocation")
			{
	    		string num;
	    		int index;

	    		index = value.find(" ");
	    		num = value.substr(0, index);
	    		int startLocationY = atoi(num.c_str());
	    		index = value.find(" ", index + 1);
	    		num = value.substr(num.length(), index);
	    		int startLocationX = atoi(num.c_str());
	    		startLocation = new Location(startLocationX, startLocationY);
	    		num = value.substr(index + 1, value.length() - index);
	    		startLocationYaw = atoi(num.c_str());
			}
	    	else if (parameter == "robotSize")
			{
	    		int index;

	    		index = value.find(" ");
	    		robotWidth = atoi(value.substr(0, index).c_str());
	    		robotHeight = atoi(value.substr(index + 1, value.length() - index).c_str());
			}
	    	else if (parameter == "MapResolutionCM")
			{
	    		mapResolution = atof(value.c_str());
			}
	    	 }
	    myfile.close();
	  }
	  else
	  {
		  cout << "Unable to open file";
	  }
}

string ConfigManager::GetMapUrl()
{
	return mapUrl;
}
Location* ConfigManager::GetStartLocationMapResolution()
{
	return startLocation;
}
Location* ConfigManager::GetStartLocationRealWorldResolution()
{
	double resolution = GetMapResolution();

	return new Location(ceil((startLocation->getX() * resolution) + resolution / 2),
					 ceil((startLocation->getY() * resolution) + resolution / 2));
}
int ConfigManager::GetstartLocationYaw()
{
	return startLocationYaw;
}

int ConfigManager::GetRobotWidth()
{
	return robotWidth;
}
int ConfigManager::GetRobotHeight()
{
	return robotHeight;
}
double ConfigManager::GetMapResolution()
{
	return mapResolution;
}
