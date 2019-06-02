//
// Created by root on 29.05.2019.
//

#include "LightSource.h"

LightSource::LightSource(
		const Point& location,
		const Color& color,
		double brightness)
		: Point(location), _color(color), _brightness(brightness) {}

void
LightSource::setLocation(const Point& location) {
	this->_x = location.getX();
	this->_y = location.getY();
	this->_z = location.getZ();
}

const Color&
LightSource::getColor() const {
	return _color;
}

void
LightSource::setColor(const Color& color) {
	_color = color;
}

double
LightSource::getBrightness() const {
	return _brightness;
}

void
LightSource::setBrightness(double brightness) {
	_brightness = brightness;
}
