//file: Point.c

#include <stdio.h>
#include <math.h>
#include "Point.h"

//#include “BOOLEAN.h”

//konstruktor
Point makePoint(int _x, int _y){
	Point temp;
	temp.x = _x;
	temp.y = _y;
	return temp;
}

//selektor
int getAbsis(Point p){
	return p.x;
}
int getOrdinat(Point p){
	return p.y;
}

//setter
void setAbsis(Point *p, int _x){
	(*p).x = _x;
}
void setOrdinat(Point *p, int _y){
	(*p).y = _y;
}
