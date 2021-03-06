//
// Created by root on 28.08.19.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "../math/Point.h"
#include "Solid.h"

class Sphere : public Solid {
private:
	Point  _position;
public:
	const Point&
	getPosition() const;

	void
	setPosition(const Point& position);

	double
	getRadius() const;

	void
	setRadius(double radius);

private:
	double _radius;
public:
	Sphere() = delete;

	explicit Sphere(Point);

	Sphere(Point,
	       double);

	uint8_t getType() const override;
};

#endif //RAYTRACING_SPHERE_H
