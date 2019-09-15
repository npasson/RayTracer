//
// Created by root on 29.05.2019.
//

#include <cmath>
#include "Color.h"
#include "misc.h"

Color::Color() {
	this->_red   = 0;
	this->_green = 0;
	this->_blue  = 0;
}

Color::Color(double brightness) {
	this->_red   = brightness;
	this->_green = brightness;
	this->_blue  = brightness;
}

Color::Color(double r,
             double g,
             double b) {
	this->_red   = r;
	this->_green = g;
	this->_blue  = b;
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

Color
Color::combine(const std::vector<Color>& colors) {
	Color total = {0, 0, 0};

	auto amount = colors.size();

	for (Color c : colors) {
		total = {
			total.getRed() + ( c.getBrightness() * c.getRed() * ( 1.0 / amount )),
			total.getGreen() + ( c.getBrightness() * c.getGreen() * ( 1.0 / amount )),
			total.getBlue() + ( c.getBrightness() * c.getBlue() * ( 1.0 / amount ))
		};
	}

	return total;
}

Color
Color::operator+(Color rhs) {
	return
		{
			this->_red + rhs._red,
			this->_green + rhs._green,
			this->_blue + rhs._blue,
		};
}

Color
Color::operator+=(Color rhs) {
	return ( *this ) = ( *this ) + rhs;
}

Color
Color::operator*(Color rhs) const {
	return {
		this->_red * rhs._red,
		this->_green * rhs._green,
		this->_blue * rhs._blue,
	};
}

