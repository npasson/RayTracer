//
// Created by root on 29.05.2019.
//

#include "Vec3.h"
#include "misc.h"
#include <cmath>
#include <iostream>

Vec3::Vec3()
	: _x(0), _y(0), _z(0) {
}

Vec3::Vec3(double x,
           double y,
           double z)
	: _x(x), _y(y), _z(z) {
}

double
Vec3::getX() const {
	return _x;
}

void
Vec3::setX(double x) {
	Vec3::_x = x;
}

double
Vec3::getY() const {
	return _y;
}

void
Vec3::setY(double y) {
	Vec3::_y = y;
}

double
Vec3::getZ() const {
	return _z;
}

void
Vec3::setZ(double z) {
	Vec3::_z = z;
}

double
Vec3::getLength() const {
	return std::sqrt(
		( _x * _x )
		+ ( _y * _y )
		+ ( _z * _z )
	);
}

Vec3
Vec3::getNormalize() const {
	if (this->getLength() == 0) {
		return {0,
		        0,
		        0};
	}
	return {_x / getLength(),
	        _y / getLength(),
	        _z / getLength()};
}

Vec3
Vec3::operator+(Vec3 rhs) const {
	return {this->_x + rhs._x,
	        this->_y + rhs._y,
	        this->_z + rhs._z};
}

Vec3
Vec3::operator+(double t) const {
	return *this + ( this->getNormalize() * t );
}

double
Vec3::operator*(Vec3 rhs) const {
	return ( this->_x * rhs._x )
	       + ( this->_y * rhs._y )
	       + ( this->_z * rhs._z );
}

Vec3
Vec3::operator*(double t) const {
	return {
		this->_x * t,
		this->_y * t,
		this->_z * t
	};
}

double
Vec3::angleInDegreesTo(Vec3 rhs) const {

	//                    u * v         180
	// return arccos ( ----------- ) * -----
	//                  |u| * |v|       PI

	double dotProduct = ( *this ) * rhs;

	double divider = this->getLength() * rhs.getLength();

	//double dotProduct = (_x * rhs._x) + (_y * rhs._y) +(_z * rhs._z);
	//double thisLength = std::sqrt()

	return std::acos(

		dotProduct / divider

	) * 180.0 / M_PI;
}

Vec3
operator*(double lhs,
          Vec3 rhs) {
	return {lhs * rhs._x,
	        lhs * rhs._y,
	        lhs * rhs._z};
}

std::ostream&
operator<<(std::ostream& lhs,
           Vec3 rhs) {
	lhs
		<< "("
		<< rhs._x << ","
		<< rhs._y << ","
		<< rhs._z
		<< ")";
	return lhs;
}
