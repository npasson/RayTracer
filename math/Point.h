//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H

#include "../generic/defines.h"
#include "Ray3.h"
#include "Vec3.h"
#include "Color.h"

class LightSource;

class Point : public Vec3 {

	//     z
	//     |_ y
	//    /
	//   x

public:
	Point();

	Point(
			double x,
			double y,
			double z);

	double
	getDistanceTo(Point) const;

	double
	getDistanceTo(
			double x,
			double y,
			double z) const;

	Ray3
	getRayTo(Point) const;

	Ray3
	getRayTo(
			double x,
			double y,
			double z) const;

	Color
	getBrightnessFromLightSource(LightSource) const;

	Point&
	getPoint();

	friend std::ostream&
	operator<<(
			std::ostream&,
			Point);
};

#endif //RAYTRACING_POINT_H