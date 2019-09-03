//
// Created by root on 29.05.2019.
//

#include <cmath>
#include <algorithm>
#include "Camera.h"
#include "../math/Color.h"
#include "../math/misc.h"
#include "../Bitmap.h"
#include "LightSource.h"

Camera::Camera(Ray3 ray)
	: _position(ray) {
}

Camera&
Camera::getInstance() {
	static Camera _instance(
		{
			{0, 0, 0},
			{1, 0, 0},
			1
		}
	);

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
Camera::forEachPixel(Color (* callback)(Ray3,
                                        uint16_t,
                                        uint16_t)) {

	auto image = new byte_t[_yRes][_xRes][Bitmap::BYTES_PER_PIXEL];

	const Vec3& origin = this->_position
	                         .getOrigin();

	double max = 1;
	double min = 0;

	for (uint16_t x = 0; x < _xRes; ++x) {
		for (uint16_t y = 0; y < _yRes; ++y) {

			Ray3 pixelRay = {
				{origin},
				getPixelCoordinate(x, y)
			};

			Color c = callback(pixelRay, x, y);

			double red   = c.getRed();
			double green = c.getGreen();
			double blue  = c.getBlue();

			double local_max = std::max({red, green, blue});
			double local_min = std::min({red, green, blue});

			if (local_max > max) {
				max = local_max;
			}

			if (local_min < min) {
				min = local_min;
			}

			image[x][y][Bitmap::RED]   = static_cast<uint8_t>(red * 255 );
			image[x][y][Bitmap::GREEN] = static_cast<uint8_t>(green * 255 );
			image[x][y][Bitmap::BLUE]  = static_cast<uint8_t>(green * 255 );
		}
	}

	for (uint16_t x = 0; x < _xRes; ++x) {
		for (uint16_t y = 0; y < _yRes; ++y) {
			image[x][y][Bitmap::RED] = static_cast<uint8_t>(
				rt_math::clamp(static_cast<double>(
					               image[x][y][Bitmap::RED]
				               )
				               / max + min, 0, 255)
			);

			image[x][y][Bitmap::GREEN] = static_cast<uint8_t>(
				rt_math::clamp(static_cast<double>(
					               image[x][y][Bitmap::GREEN
					               ])
				               / max + min, 0, 255)
			);
			image[x][y][Bitmap::BLUE]  = static_cast<uint8_t>(
				rt_math::clamp(static_cast<double>(
					               image[x][y][Bitmap::BLUE]
				               )
				               / max + min, 0, 255)
			);

		}
	}

	std::string imageFileName = "bitmapImage4.bmp";

	Bitmap::saveImage(reinterpret_cast<byte_t*>(image), _xRes, _yRes, imageFileName);

	delete[] image;
	IFDEBUG(std::cout << "Generated!" << std::endl;)
}

double inline
Camera::getAspectRatio() const {
	return static_cast<double>(_xRes) / _yRes;
}

Vec3
Camera::getPixelCoordinate(uint16_t x,
                           uint16_t y) const {

	double scale = tan(rt_math::deg2rad(getFov() * 0.5));

	double x_space = ( 2 * ( x + 0.5 ) / _xRes - 1 ) * getAspectRatio() * scale;
	double y_space = ( 1 - 2 * ( y + 0.5 ) / _yRes ) * scale;

	return {1,
	        x_space,
	        y_space};
}

uint16_t
Camera::getXRes() const {
	return _xRes;
}

//void
//Camera::setXRes(uint16_t xRes) {
//	_xRes = xRes;
//}

uint16_t
Camera::getYRes() const {
	return _yRes;
}

void
Camera::render() {
	this->forEachPixel([](Ray3 ray,
	                      uint16_t x,
	                      uint16_t y) -> Color {
		//std::cout << ray << std::endl;
		auto solids = Solid::getSolids();

		std::vector<std::pair<Solid, Point>> hits;

		while (!solids.empty()) {
			Solid* s = solids.front();
			solids.pop();

			Point* p = ray.getIntersect(*s);

			if (p == nullptr) {
				continue;
			}

			hits.emplace_back(*s, *p);

			delete p;

		}

		if (hits.empty()) {
			return {0, 0, 0};
		}

		std::sort(hits.begin(),
		          hits.end(),
		          [&](std::pair<Solid, Point> lhs,
		              std::pair<Solid, Point> rhs) -> bool {
			          return Point(ray.getOrigin()).getDistanceTo(lhs.second)
			                 < Point(ray.getOrigin()).getDistanceTo(rhs.second);
		          });

		Point hit_point = hits.front()
		                      .second;
		Solid hit_solid = hits.front()
		                      .first;

		/*

		auto lights = LightSource::getLights();

		std::vector<Color> lighting;

		while (!lights.empty()) {
			LightSource* ls = lights.front();
			lights.pop();

			lighting.push_back(p.getBrightnessFromLightSource(*ls));
		}

		Color combined = Color::combine(lighting);

		return combined;
		 */

		return rt_math::phong(hit_point, hit_solid, ray.getDirection());
	});
}

//void
//Camera::setYRes(uint16_t yRes) {
//	_yRes = yRes;
//}
