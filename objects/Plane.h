//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H


#include "../math/Ray3.h"

class Plane {
public:
	Plane(Vec3, Vec3); // normal form

protected:
	Vec3 _origin;
public:
	const Vec3&
	getOrigin() const;

	void
	setOrigin(const Vec3& origin);

	const Vec3&
	getNormal() const;

	void
	setNormal(const Vec3& normal);

protected:
	Vec3 _normal;
};


#endif //RAYTRACING_PLANE_H
