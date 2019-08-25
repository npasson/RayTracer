//
// Created by root on 29.05.2019.
//

#include <cmath>
#include "Point.h"
#include "../objects/LightSource.h"

Point::Point()
	: Vec3() {
}

Point::Point(double x,
             double y,
             double z)
	: Vec3(x, y, z) {
}

double
Point::getDistanceTo(Point p) const {
	return Vec3(
		p._x - this->_x,
		p._y - this->_y,
		p._z - this->_z
	).getLength();
}

double
Point::getDistanceTo(double x,
                     double y,
                     double z) const {
	return Vec3(
		x - this->_x,
		y - this->_y,
		z - this->_z
	).getLength();
}

Ray3
Point::getRayTo(Point p) const {
	Vec3 pointing = {p._x - this->_x,
	                 p._y - this->_y,
	                 p._z - this->_z};
	return {*this,
	        pointing,
	        pointing.getLength()};
}

Ray3
Point::getRayTo(double x,
                double y,
                double z) const {
	return getRayTo({x, y, z});
}

Color
Point::getBrightnessFromLightSource(LightSource ls) const {
	return (
		(
			ls.getColor()
			/ std::sqrt(
				this->getDistanceTo(ls.getPoint())
			)
		)
		* ls.getBrightness()
	);
}

std::ostream&
operator<<(std::ostream& lhs,
           Point rhs) {
	lhs
		<< "{"
		<< rhs._x << ","
		<< rhs._y << ","
		<< rhs._z
		<< "}";
	return lhs;
}

Point&
Point::getPoint() {
	return *this;
}
