//
// Created by root on 29.05.2019.
//

#include "Plane.h"

Plane::Plane(
		const Vec3& origin,
		const Vec3& direction)
		: Ray3(origin, direction.getNormalize(), 1) {}
