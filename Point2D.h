/*
* File:   Point2D.h
* Author: George
*
* Created on 12 George 2014 �., 18:04
*/

#ifndef POINT2D_H
#define	POINT2D_H

#include <iostream>

using namespace std;

class Point2D {
public:
	Point2D(double a = 0);
	Point2D(double tx, double ty);
	double getX() const;
	double getY() const;
	bool setX(double tx);
	bool setY(double ty);
	void print() const;
private:
	double x, y;
};

#endif	/* POINT2D_H */
