#include "basicLibrary.h"
#include <stdio.h> //needed for printf command

#include <math.h>
#include "basicLibrary.h"

point2D::point2D(){
	x = 0;
	y = 0;
	//printf("made a point2D \n");
}

point2D::point2D(float xIn, float yIn){
	x = xIn;
	y = yIn;
	//printf("made a point2D, with 2 parameters \n");	
}

float point2D::distance(point2D p2){
	float dist = sqrt(pow(p2.x-x,2) + pow(p2.y-y, 2));
	return dist;
}

float point2D::fastDistance(point2D p2){
	float fDist = pow(p2.x-x,2) + pow(p2.y-y, 2);
	return fDist;
}

/*
point2D point2D::movePoint(vec2D v){
	point2D n();
	n.x = x + v.x;
	n.y = y + v.y;
	return n;
}
*/

/*point2D point2D::movePoint(vec2D v){
	float point = ((x,y)+v);
	return point;
}*/

vec2D::vec2D(){

}

vec2D::vec2D(float xIn, float yIn){
	x = xIn;
	y = yIn;
	length();
}

float vec2D::length(){
	float L = sqrt((pow(x,2) + pow(y,2)));
	mag = L;
	return L;
}

vec2D vec2D::normalize(){
	vec2D normVec(x,y);
	normVec.x = x/mag;
	normVec.y = y/mag;
	if (normVec.length() == 1){
		return normVec;
	}
	return normVec;
}

vec2D vec2D::vectorMultiply(float scalar){
	vec2D multVec(x,y);
	multVec.x = x*scalar;
	multVec.y = y*scalar;
	multVec.length();
	return multVec;
}

vec2D vec2D::createVector(point2D p1, point2D p2){
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	length();
	vec2D newVec(x,y);
	return newVec;
}

colour::colour(){

}