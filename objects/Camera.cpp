//
// Created by root on 29.05.2019.
//

#include <iostream>
#include <cmath>
#include "Camera.h"
#include "../math/Color.h"
#include "../math/misc.h"

Camera::Camera(Ray3 ray)
		: _position(ray) {}

Camera&
Camera::getInstance() {
	static Camera _instance({{0, 0, 0}, {1, 0, 0}, 1});
	return _instance;
}

const Ray3&
Camera::getPosition() const {
	return _position;
}

void
Camera::setPosition(const Ray3& position) {
	Camera::_position = position;
}

double
Camera::getFov() const {
	return _fov;
}

void
Camera::setFov(double fov) {
	Camera::_fov = fov;
}

void
Camera::forEachPixel(
		Color (* callable)(
				Ray3,
				uint16_t,
				uint16_t)) {

	double distance = _xRes / tan(rt_math::deg2rad(_fov / 2));

	const Vec3& origin = this->_position
	                         .getOrigin();

	for (uint16_t x = 0; x < _xRes; ++x) {
		for (uint16_t y = 0; y < _yRes; ++y) {
			Vec3 thisPixel = {distance,
			                  ( x - ( _xRes / 2.0 )) + 0.5,
			                  ( y - ( _yRes / 2.0 )) + 0.5};
			Ray3 pixel     = {{origin},
			                  thisPixel.getNormalize()};

			callable(pixel, x, y);
		}
	}
}

double inline
Camera::getAspectRatio() const {
	return static_cast<double>(_xRes) / _yRes;
}

double
Camera::getPixelNDCX(uint16_t px) const {
	return ( static_cast<double>(px) + 0.5 ) / _xRes;
}

double
Camera::getPixelNDCY(uint16_t px) const {
	return ( static_cast<double>(px) + 0.5 ) / _yRes;
}

double
Camera::getPixelScreenX(uint16_t px) const {
	return ( 2.0 * getPixelNDCX(px)) - 1.0;
}

double
Camera::getPixelScreenY(uint16_t) const {
	return 1.0 - ( 2.0 * getPixelNDCY(px));
}


double
Camera::getPixelCameraX(uint16_t px) const {
	return ( 2 * getPixelScreenX(px) - 1 ) * getAspectRatio();
}

double
Camera::getPixelCameraY(uint16_t px) const {
	return 1 - ( 2 * getPixelScreenY(px));
}

Vec3
Camera::getPixelCoordinate(
		uint16_t x,
		uint16_t y) const {
	return {getPixelCameraX(x),
	        getPixelCameraY(y),
	        1};
}