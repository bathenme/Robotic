
#ifndef LOCATION_H_
#define LOCATION_H_

#include <math.h>

class Location {
private :
	float _x;
	float _y;

	void construct(float x,float y);

public:
	//**********************
	//		Ctor
	//**********************
	Location();
	Location(float x,float y);

	//**********************
	//		Accessors
	//**********************

	float getX() const {
		return _x;
	}

	void setX(float x) {
		_x = x;
	}

	float getY() const {
		return _y;
	}

	void setY(float y) {
		_y = y;
	}

	//**************************
	//     Magnitude and distance
	//**************************
	inline float Magnitude(const Location& v)
	{
	    return (sqrtf(v.getX() * v.getX() + v.getY() * v.getY()));
	}

	inline float Distance(const Location& v)
	{
		return (sqrtf((v.getX() - getX()) * (v.getX() - getX())
				+ (v.getY() - getY()) * (v.getY() - getY())));
	}

	Location operator -(const Location& v) const
	{
	    return (Location(_x - v._x, _y - v._y));
	}

	Location& operator /=(float t)
	{
	    float f = 1.0F / t;
	    _x *= f;
	    _y *= f;
	    return (*this);
	}

	Location& Normalize(void)
	{
	    return (*this /= sqrtf(_x * _x + _y * _y));
	}
};

#endif
