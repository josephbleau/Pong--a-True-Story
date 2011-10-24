#include "Vec2d.h"

Vec2d::Vec2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2d::~Vec2d()
{

}

bool Vec2d::operator==(const Vec2d &v2)
{
	if(this->x == v2.x &&
	   this->y == v2.y)
		return true;

	return false;
}