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

	uint16_t _xRes = 10;
	uint16_t _yRes = 10;
public:
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

	double
	getPixelNDCX(uint16_t) const;

	double
	getPixelNDCY(uint16_t) const;

	double
	getPixelScreenX(uint16_t) const;

	double
	getPixelScreenY(uint16_t) const;

	double
	getPixelCameraX(uint16_t) const;

	double
	getPixelCameraY(uint16_t) const;

	Vec3
	getPixelCoordinate(uint16_t,
	                   uint16_t) const;

public:
	Camera(Camera const&) = delete;

	void
	operator=(Camera const&) = delete;
};

#endif //RAYTRACING_CAMERA_H
