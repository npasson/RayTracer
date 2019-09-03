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

	const static uint16_t _xRes = 1000;
	const static uint16_t _yRes = 1000;
public:
	uint16_t
	getXRes() const;

	uint16_t
	getYRes() const;


	void
	render();

	void
	forEachPixel(Color (* callback)(Ray3,
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
	double _fov = 90;

	double inline
	getAspectRatio() const;

	Vec3
	getPixelCoordinate(uint16_t,
	                   uint16_t) const;

public:
	Camera(Camera const&) = delete;

	void
	operator=(Camera const&) = delete;
};

#endif //RAYTRACING_CAMERA_H
