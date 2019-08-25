//
// Created by root on 29.05.2019.
//

#include "LightSource.h"

std::queue<LightSource*> LightSource::lights = std::queue<LightSource*>{};

const std::queue<LightSource*>&
LightSource::getLights() {
	return lights;
}

LightSource::LightSource(const Point& location,
                         const Color& color,
                         double brightness)
	: Point(location),
	  _color(color),
	  _brightness(brightness) {
	LightSource::lights.emplace(this);
}

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
