#ifndef VEC2D_H
#define VEC2D_H

class Vec2d
{
public:
	float x, y;

	Vec2d(float x, float y);
	~Vec2d();

	bool operator==(const Vec2d &v2);
};

#endif 