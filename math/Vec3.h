//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <initializer_list>
#include <ostream>
#include "../generic/defines.h"

class Vec3 {
protected:
	double _x;
	double _y;
	double _z;
public:
	Vec3();

	Vec3(double x,
	     double y,
	     double z);

	double
	getX() const;

	void
	setX(double x);

	double
	getY() const;

	void
	setY(double y);

	double
	getZ() const;

	void
	setZ(double z);

	double
	getLength() const;

	Vec3
	getNormalize() const;

	Vec3
	reflectOff(Vec3&);

	Vec3
	operator+(Vec3) const;

	Vec3
	operator+(double) const;

	Vec3
	operator-() const;

	Vec3
	operator-(Vec3) const;

	double
	operator*(Vec3) const;

	Vec3
	operator*(double) const;

	double
	angleInDegreesTo(Vec3) const;

	friend Vec3
	operator*(double,
	          Vec3);

	friend std::ostream&
	operator<<(std::ostream&,
	           Vec3);
};

#endif //RAYTRACING_VEC3_H
