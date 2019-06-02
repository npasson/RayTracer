//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H


#include <cstdint>
#include "../math/Ray3.h"
#include "../math/Color.h"

class Camera {
public:
	static Camera&
	getInstance();

private:
	Camera(Ray3); //NOLINT

	Ray3 _position;

	uint16_t _xRes = 1920;
	uint16_t _yRes = 1080;
public:
	void
	forEachPixel(
			Color (* callable)(
					Ray3,
					uint16_t,
					uint16_t));

	const Ray3&
	getPosition() const;

	void
	setPosition(const Ray3& position);

	double
	getFov() const;

	void
	setFov(double fov);

private:
	double _fov = 60;
public:
	Camera(Camera const&) = delete;

	void
	operator=(Camera const&) = delete;
};

#endif //RAYTRACING_CAMERA_H
