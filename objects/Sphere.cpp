//
// Created by root on 28.08.19.
//

#include "Sphere.h"

Sphere::Sphere(Point location,
               double radius)
	: Solid() {
	this->_position = location;
	this->_radius   = radius;
}

Sphere::Sphere(Point location)
	: Solid() {
	this->_position = location;
	this->_radius   = 1;
}


