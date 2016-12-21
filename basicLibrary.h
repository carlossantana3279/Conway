#ifndef __BASICLIBRARY_H__	//guard against cyclic dependancy
#define __BASICLIBRARY_H__

class point2D;
class vec2D;
class colour;

class point2D{
public:
	point2D();
	point2D(float xIn, float yIn);

	float x,y;
	float distance (point2D p2);
	float fastDistance (point2D p2);
	point2D movePoint (vec2D v);

private:

};

class vec2D{
public:
	vec2D();
	vec2D(float xIn, float yIn);

	float x, y, mag;

	float length();
	vec2D normalize();
	vec2D vectorMultiply(float scalar);
	vec2D createVector(point2D p1, point2D p2);

private:

};

class colour{
public:
	colour();
	colour(float rIn, float gIn, float bIn);

	float r, g, b;

private:

};

#endif