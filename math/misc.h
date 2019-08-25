//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_MISC_H
#define RAYTRACING_MISC_H

#include <cmath>

#include "Ray3.h"
#include "Matrix.h"

namespace rt_math {

	enum Axes {
		X, Y, Z
	};

	inline double
	clamp(double value,
	      double min,
	      double max) {
		if (value > max) { return max; }
		if (value < min) { return min; }
		return value;
	}

	inline double
	deg2rad(double degrees) {
		return ( degrees * M_PI ) / 180;
	}

	inline Ray3
	rotateVector(Ray3 ray,
	             Axes axis,
	             double degrees) {
		// TODO
		Matrix rotationMatrix(3, 3);

		degrees = deg2rad(degrees);

		if (axis == X) {
			rotationMatrix = {{1, 0,            0},
			                  {0, cos(degrees), -sin(degrees)},
			                  {0, sin(degrees), cos(degrees)}};
		} else if (axis == Y) {
			rotationMatrix = {{cos(degrees),  0, sin(degrees)},
			                  {0,             1, 0},
			                  {-sin(degrees), 0, cos(degrees)}};
		} else {
			rotationMatrix = {{cos(degrees), -sin(degrees), 0},
			                  {sin(degrees), cos(degrees),  0},
			                  {0,            0,             1}};
		}

		Matrix directional(Matrix::_t{{ray.getDirection()
		                                  .getX()},
		                              {ray.getDirection()
		                                  .getY()},
		                              {ray.getDirection()
		                                  .getZ()}});

		Matrix rotated = rotationMatrix * directional;

		Ray3 rotatedRay(ray.getOrigin(),
		                {rotated.getData()[0][0],
		                 rotated.getData()[1][0],
		                 rotated.getData()[2][0]},
		                ray.getDistance());

		return rotatedRay;
	}
}

#endif //RAYTRACING_MISC_H
