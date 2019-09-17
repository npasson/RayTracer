//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_RAY3_H
#define RAYTRACING_RAY3_H

#include <ostream>
#include "Vec3.h"

class Point;

class Solid;

class Ray3 {
public:
	Ray3(const Vec3& origin,
	     Vec3 direction,
	     double distance);

	Ray3(const Vec3& origin,
	     Vec3 direction);

	enum Axes {
		X, Y, Z, UP, DOWN, LEFT, RIGHT, ROLL_LEFT, ROLL_RIGHT
	};

	Ray3
	rotate(Axes axis,
	       double degrees);

	const Vec3&
	getOrigin() const;

	void
	setOrigin(const Vec3& origin);

	const Vec3&
	getDirection() const;

	void
	setDirection(const Vec3& direction);

	double
	getDistance() const;

	void
	setDistance(double distance);

	double
	getMinDistanceTo(Point);

	Point*
	getIntersect(const Solid&);

	Point
	getEndPoint();

	friend std::ostream&
	operator<<(std::ostream&,
	           Ray3);

protected:
	Vec3   _origin;
	Vec3   _direction;
	double _distance;
};

#endif //RAYTRACING_RAY3_H
