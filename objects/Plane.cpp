//
// Created by root on 29.05.2019.
//

#include "Plane.h"

Plane::Plane(Vec3 origin,
             Vec3 normal) {
	_origin = origin;
	if (normal.getLength() == 0) {
		// if normal is zero, make it point straight up
		// TODO error out here
		_normal = {0,
		           0,
		           1};
	} else {
		_normal = normal.getNormalize();
	}
}

const Vec3&
Plane::getOrigin() const {
	return _origin;
}

void
Plane::setOrigin(const Vec3& origin) {
	_origin = origin;
}

const Vec3&
Plane::getNormal() const {
	return _normal;
}

void
Plane::setNormal(const Vec3& normal) {
	_normal = normal;
}
