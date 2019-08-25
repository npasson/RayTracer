//
// Created by root on 29.05.2019.
//

#include <cmath>
#include "Color.h"
#include "misc.h"

Color::Color() {
	this->_red   = 0.5;
	this->_green = 0.5;
	this->_blue  = 0.5;
}

Color::Color(double brightness) {
	brightness = rt_math::clamp(brightness, 0, 1);
	this->_red   = brightness;
	this->_green = brightness;
	this->_blue  = brightness;
}

Color::Color(double r,
             double g,
             double b) {
	this->_red   = rt_math::clamp(r, 0, 1);
	this->_green = rt_math::clamp(g, 0, 1);
	this->_blue  = rt_math::clamp(b, 0, 1);
}

double
Color::getBrightness() {
	return std::sqrt(( _red * _red ) + ( _green * _green ) + ( _blue * _blue ));
}

Color
Color::operator*(double rhs) const {
	return {rhs * _red,
	        rhs * _green,
	        rhs * _blue};
}

Color
Color::operator/(double rhs) const {
	return ( *this ) * ( 1 / rhs );
}

double
Color::getRed() const {
	return _red;
}

void
Color::setRed(double red) {
	_red = red;
}

double
Color::getGreen() const {
	return _green;
}

void
Color::setGreen(double green) {
	_green = green;
}

double
Color::getBlue() const {
	return _blue;
}

void
Color::setBlue(double blue) {
	_blue = blue;
}

byte_t
Color::toByte(double color) {
	return static_cast<byte_t>(color * 256);
}

std::ostream&
operator<<(std::ostream& lhs,
           Color rhs) {
	lhs
		<< "("
		<< rhs._red << ","
		<< rhs._green << ","
		<< rhs._blue
		<< ")";
	return lhs;
}

