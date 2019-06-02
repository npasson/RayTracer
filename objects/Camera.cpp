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

//	double verticalFov = ( static_cast<double>(_yRes) / _xRes ) * _fov;
//	double horizontalFov = _fov;
//
//	Ray3 topLeft = this->_position;
//	topLeft = topLeft.rotate(Ray3::Z, -( horizontalFov / 2 ));
//
//	std::cout << "Debug output: topLeft = " << topLeft << std::endl;
//
//	topLeft = topLeft.rotate(Ray3::UP, ( verticalFov / 2 )); // FIXME Not only Y, but X and Y combined somehow
//
//	std::cout << "Debug output: topLeft = " << topLeft << std::endl;
//	std::cout << "Debug output: bottomRight = "
//	          << topLeft.rotate(Ray3::Z, ( horizontalFov / 2 ))
//	                    .rotate(Ray3::DOWN, ( verticalFov / 2 ))
//	          << std::endl;
//
//
//	Ray3 current{{0, 0, 0},
//	             {0, 0, 0}};
//
//	for (uint16_t y = 0; y < _yRes; ++y) {
//		for (uint16_t x = 0; x < _xRes; ++x) {
//			current = topLeft.rotate(Ray3::Z, (( horizontalFov * x ) / _xRes ));
//			current = current.rotate(Ray3::DOWN, (( verticalFov * y ) / _yRes ));
//
//			callable(current, x, y);
//		}
//	}
}