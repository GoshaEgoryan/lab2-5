/*
* File:   Object2DA9.cpp
* Author: George
*
* Created on 14.11.2014, 1:07
*/

#include <cmath>
#include "Object2DA9.h"

Object2DA9::Object2DA9(const Object2DA9* object) {
    create(
        object->getA(),
        object->getB(),
        object->getC(),
        object->getD(),
        object->getCentre(),
        object->getAngle()
        );
}

Object2DA9::Object2DA9(double ta, double tb, double tc, double td, const Point2D* tcentre, double tangle) {
    create(ta, tb, tc, td, tcentre, tangle);
}

Object2DA9::Object2DA9(double ta, double tb, double tc, double td, double tx, double ty, double tangle) {
    create(ta, tb, tc, td, new Point2D(tx, ty), tangle);
}

double Object2DA9::getA() const {
    return p_a;
}

double Object2DA9::getB() const {
    return p_b;
}

double Object2DA9::getC() const {
    return p_c;
}

double Object2DA9::getD() const {
    return p_d;
}

double Object2DA9::getAngle() const {
    return p_angle;
}

Point2D* Object2DA9::getCentre() const {
    return new Point2D(p_centre_x, p_centre_y);
}

double Object2DA9::getCentreX() const {
    return p_centre_x;
}

double Object2DA9::getCentreY() const {
    return p_centre_y;
}

Object2DA9* Object2DA9::getClone() const {
    return new Object2DA9(this);
}

bool Object2DA9::setA(double ta) {
    if (checkCorrectA(ta)) {
        p_a = ta;
        return true;
    };
    return false;
}

bool Object2DA9::setB(double tb) {
    if (checkCorrectB(tb)) {
        p_b = tb;
        return true;
    };
    return false;
}

bool Object2DA9::setC(double tc) {
    if (checkCorrectC(tc)) {
        p_c = tc;
        return true;
    };
    return false;
}

bool Object2DA9::setD(double td) {
    if (checkCorrectD(td)) {
        p_d = td;
        return true;
    };
    return false;
}

bool Object2DA9::setAngle(double tangle) {
    p_angle = tangle;
    return true;
}

bool Object2DA9::setCentre(const Point2D* tcentre) {
    p_centre_x = tcentre->getX();
    p_centre_y = tcentre->getY();
    return true;
}

bool Object2DA9::setCentre(double tx, double ty) {
    p_centre_x = tx;
    p_centre_y = ty;
    return true;
}

bool Object2DA9::setCentreX(double tx) {
    p_centre_x = tx;
    return true;
}

bool Object2DA9::setCentreY(double ty) {
    p_centre_y = ty;
    return true;
}

void Object2DA9::setAll(const Object2DA9* object) {
	setAll(
		object->getA(),
		object->getB(),
		object->getC(),
		object->getD(),
		object->getCentre(),
		object->getAngle()
		);
}

void Object2DA9::setAll(double ta, double tb, double tc, double td, const Point2D* tcentre, double tangle) {
	double a = p_a, b = p_b, c = p_c, d = p_d;
	bool verification = false;
	do {
		if ((ta < 0) || (tb < 0) || (tc < 0) || (td < 0)) {
			verification = true;
			break;
		};
		p_a = ta;
		if ((2 * tb) <= p_a) {
			p_b = tb;
		}
		else {
			verification = true;
			break;
		};
		if ((tc <= p_a) && ((p_b + hypotenuse(tc) / 2) < hypotenuse(p_a, p_a / 2))) {
			p_c = tc;
		}
		else {
			verification = true;
			break;
		};
		if (!setD(td)) {
			verification = true;
			break;
		};
	} while (0);
	if (verification) {
		p_a = a;
		p_b = b;
		p_c = c;
		p_d = d;
		return;
	}
	setAngle(tangle);
	p_centre_x = tcentre->getX();
	p_centre_y = tcentre->getY();
}

void Object2DA9::setAll(double ta, double tb, double tc, double td, double tx, double ty, double tangle) {
	setAll(ta, tb, tc, td, new Point2D(tx, ty), tangle);
}

bool Object2DA9::move(double x, double y, double tangle) {
    p_centre_x += x;
    p_centre_y += y;
    rotate(tangle);
    return true;
}

bool Object2DA9::move(const Point2D* delta, double tangle) {
    move(delta->getX(), delta->getY(), tangle);
    return true;
}

bool Object2DA9::rotate(double tangle) {
    setAngle(p_angle + tangle);
    return true;
}

bool Object2DA9::isInside(double x, double y) const {
    return isInside(new Point2D(x, y));
}

bool Object2DA9::isInside(const Point2D* point) const {
    return checkInside(moveAndRotatePoint(point));
}

void Object2DA9::print() const {
    cout << "a = " << p_a << ", b = " << p_b << ", c = " << p_c << ", d = " << p_d << ", angle = " << p_angle << ", centre: ";
    (new Point2D(p_centre_x, p_centre_y))->print();
}

void Object2DA9::create(double ta, double tb, double tc, double td, const Point2D* tcentre, double tangle) {
    bool verification = false;
    do {
        if ((ta < 0) || (tb < 0) || (tc < 0) || (td < 0)) {
            verification = true;
            break;
        };
        p_a = ta;
        if ((2 * tb) <= p_a) {
            p_b = tb;
        }
        else {
            verification = true;
            break;
        };
        if ((tc <= p_a) && ((p_b + hypotenuse(tc) / 2) < hypotenuse(p_a, p_a / 2))) {
            p_c = tc;
        }
        else {
            verification = true;
            break;
        };
        if (!setD(td)) {
            verification = true;
            break;
        };
    } while (0);
    if (verification) {
        p_a = p_b = p_c = p_d = 0;
    }
    setAngle(tangle);
    p_centre_x = tcentre->getX();
    p_centre_y = tcentre->getY();
}

Point2D* Object2DA9::moveAndRotatePoint(const Point2D* startPoint) const {
    double x, y;
    Point2D* point = movePoint(startPoint);
    x = point->getX() * cos(-p_angle) - point->getY() * sin(-p_angle);
    y = point->getX() * sin(-p_angle) + point->getY() * cos(-p_angle);
    point->setX(x);
    point->setY(y);
    return point;
}

Point2D* Object2DA9::movePoint(const Point2D* point) const {
    return new Point2D(point->getX() - p_centre_x, point->getY() - p_centre_y);
}

double Object2DA9::hypotenuse(double x, double y) const {
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Object2DA9::hypotenuse(double a) const {
    return a * sqrt(2);
}

bool Object2DA9::checkCorrectA(double ta) const {
    if (ta < 0) return false;
    return ((p_b + p_d) < hypotenuse(ta, ta / 2)) && ((p_b + hypotenuse(p_c) / 2) < hypotenuse(ta, ta / 2)) && ((p_c + p_d) <= ta) && (2 * p_b <= ta);
}

bool Object2DA9::checkCorrectB(double tb) const {
    if (tb < 0) return false;
    return ((tb + p_d) < hypotenuse(p_a, p_a / 2)) && ((tb + hypotenuse(p_c) / 2) < hypotenuse(p_a, p_a / 2)) && (2 * tb <= p_a);
}

bool Object2DA9::checkCorrectC(double tc) const {
    if (tc < 0) return false;
    return ((p_b + hypotenuse(tc) / 2) < hypotenuse(p_a, p_a / 2)) && ((tc + p_d) <= p_a);
}

bool Object2DA9::checkCorrectD(double td) const {
    if (td < 0) return false;
    return ((p_b + td) < hypotenuse(p_a, p_a / 2)) && ((p_c + td) <= p_a);
}

bool Object2DA9::checkInside(const Point2D* point) const {
    return 
        (abs(point->getX()) <= p_a / 2)
        && 
        (abs(point->getY()) <= p_a / 2)
        && 
        ((pow((point->getX() - p_a / 2), 2) + pow(point->getY(), 2)) >= pow(p_b, 2))
        &&
        (-point->getY() <= (point->getX() + p_a - p_c))
        &&
        ((pow((point->getX() + p_a / 2), 2) + pow((point->getY() - p_a / 2), 2)) >= pow(p_d, 2));
}
