//
// Created by root on 29.05.2019.
//

#include <cmath>
#include <iostream>
#include "Ray3.h"
#include "Matrix.h"
#include "misc.h"
#include "../objects/Solid.h"
#include "../objects/Sphere.h"

Ray3::Ray3(const Vec3& origin,
           const Vec3 direction,
           double distance)
	: _origin(origin.getNormalize()), _direction(direction.getNormalize()), _distance(distance) {
}

Ray3::Ray3(const Vec3& origin,
           Vec3 direction)
	: _origin(origin), _direction(direction), _distance(direction.getLength()) {
}

const Vec3&
Ray3::getOrigin() const {
	return _origin;
}

void
Ray3::setOrigin(const Vec3& origin) {
	_origin = origin;
}

const Vec3&
Ray3::getDirection() const {
	return _direction;
}

void
Ray3::setDirection(const Vec3& direction) {
	_direction = direction;
}

double
Ray3::getDistance() const {
	return _distance;
}

void
Ray3::setDistance(double distance) {
	_distance = distance;
}

std::ostream&
operator<<(std::ostream& lhs,
           Ray3 rhs) {
	lhs
		<< "{R" << rhs.getOrigin()
		<< "+x*" << rhs.getDirection()
		<< "(d" << rhs.getDistance()
		<< ")}";
	return lhs;
}

Ray3
Ray3::rotate(Axes axis,
             double degrees) {
	Matrix rotationMatrix(3, 3);
	Ray3   ray   = *this;
	double theta = rt_math::deg2rad(degrees);

	if (axis == X) {
		rotationMatrix = {{1, 0,          0},            //   [x]
		                  {0, cos(theta), -sin(theta)},  // * [y]
		                  {0, sin(theta), cos(theta)}};  //   [z]
	} else if (axis == Y) {
		rotationMatrix = {{cos(theta),  0, sin(theta)},  //   [x]
		                  {0,           1, 0},           // * [y]
		                  {-sin(theta), 0, cos(theta)}}; //   [z]
	} else if (axis == Z) {
		rotationMatrix = {{cos(theta), -sin(theta), 0},  //   [x]
		                  {sin(theta), cos(theta),  0},  // * [y]
		                  {0,          0,           1}}; //   [z]
	} else {

		if (axis == UP || axis == DOWN) {
			Vec3 target;
			if (axis == DOWN) {
				target = {0,
				          0,
				          -1};
			} else {
				target = {0,
				          0,
				          1};
			}

			double angle = ray.getDirection()
			                  .angleInDegreesTo(target);

			double percentageToStillRotate = degrees / angle;

			// get 'middle' point between the current vector and 'down',
			// taking into account how many degrees we're away from the lowest vector
			// TODO rotations beyond completely down/up are not tested, stay away.

			Ray3 rotatedRay(
				ray.getOrigin(),
				(
					(
						( 1 - percentageToStillRotate ) * ray.getDirection()
					)
					+ ( percentageToStillRotate * target )
				).getNormalize());
			return rotatedRay;
		}
	}

	Matrix directional(Matrix::_t{
		{ray.getDirection()
		    .getX()},
		{ray.getDirection()
		    .getY()},
		{ray.getDirection()
		    .getZ()}
	});

	Matrix rotated = rotationMatrix * directional;

	Ray3 rotatedRay(
		ray.getOrigin(),
		{
			rotated.getData()[0][0],
			rotated.getData()[1][0],
			rotated.getData()[2][0]
		});

	return rotatedRay;
}

Point*
Ray3::getIntersect(const Solid& solid) {
	if (solid.getType() == SPHERE) {
		auto& s = dynamic_cast<const Sphere&>(solid);

		Point rayStartPoint = Point(
			this->_origin
			    .getX(),
			this->_origin
			    .getY(),
			this->_origin
			    .getZ()
		);

		Ray3 hypothenuse = rayStartPoint.getRayTo(
			s.getPosition()
		);

		std::cout << "Camera ray: " << *this << std::endl;
		std::cout << "Object ray: " << hypothenuse << std::endl;

		Vec3 cameraVector = this->getDirection();
		Vec3 hypVector    = hypothenuse.getDirection();

		std::cout << "Camera vector: " << cameraVector << std::endl;
		std::cout << "Object vector: " << hypVector << std::endl;

		double angle = cameraVector.angleInDegreesTo(hypVector);

		std::cout << "Angle: " << angle << std::endl;

		//         s
		//        /|
		//       / |
		//    h /  |
		//     /   | d
		//    /   _|
		//   /A__|_|
		// r
		//
		// d = sin(A) * h
		//

		double sine = std::sin(rt_math::deg2rad(angle));

		std::cout << "Sine: " << sine << std::endl;

		double distance = sine * rayStartPoint.getDistanceTo(s.getPosition());

		if (distance < s.getRadius()) {
			// HIT!
			std::cout << "Hit with distance " << distance << std::endl;
			return new Point{1, 1, 1};

			double offset = std::sqrt(
				(s.getRadius() * s.getRadius())
				+ (distance * distance)
			);


		} else {
			std::cout << "No hit, distance " << distance << std::endl;
			return nullptr;
		}
	} else { return nullptr; }

}