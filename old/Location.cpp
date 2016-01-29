
#include "Location.h"

void Location::construct(float x, float y){
	this->_x = x;
	this->_y = y;
}

Location::Location() {
	this->construct(0,0);
}

Location::Location(float x, float y){
	this->construct(x,y);
}
