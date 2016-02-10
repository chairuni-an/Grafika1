//file: Point.h

#ifndef POINT_H
#define POINT_H

//#include “BOOLEAN.h”

//definisi
typedef struct{
	int x; //absis
	int y; //ordinat
} Point;

//konstruktor
Point makePoint(int _x, int _y);

//selektor
int getAbsis(Point p);
int getOrdinat(Point p);

//setter
void setAbsis(Point *p, int _x);
void setOrdinat(Point *p, int _y);

#endif
