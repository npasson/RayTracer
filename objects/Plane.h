//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H


#include "../math/Ray3.h"

class Plane : public Ray3 {
public:
	Plane(
			const Vec3& origin,
			const Vec3& direction);

};


#endif //RAYTRACING_PLANE_H
