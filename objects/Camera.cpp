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

inline static Color
adjustColor(Color originalPixel,
            double max) {
	//
	// old gamma function:
	//
		__attribute__((unused)) double gamma = 0.8;
	  return {
	  	std::pow(rt_math::clamp( originalPixel.getRed()/ max, 0, 1), gamma),
	  	std::pow(rt_math::clamp( originalPixel.getGreen()/ max, 0, 1), gamma),
	  	std::pow(rt_math::clamp( originalPixel.getBlue()/ max, 0, 1), gamma),
	  };



//	return {
//		1 - std::exp(originalPixel.getRed()   /max),
//		1 - std::exp(originalPixel.getGreen() /max),
//		1 - std::exp(originalPixel.getBlue()  /max),
//	};
}

void
Camera::forEachPixel(Color (* callback)(Ray3,
                                        uint16_t,
                                        uint16_t,
                                        Color)) {

	auto image      = new byte_t[_yRes][_xRes][Bitmap::BYTES_PER_PIXEL];
	auto image_copy = new double[_yRes][_xRes][Bitmap::BYTES_PER_PIXEL];

	const Vec3& origin = this->_position
	                         .getOrigin();

	std::vector<double> max_brightnesses;

	for (uint16_t x = 0; x < _xRes; ++x) {
		for (uint16_t y = 0; y < _yRes; ++y) {

			Ray3 pixelRay = {
				{origin},
				getPixelCoordinate(x, y)
			};

			Color c = callback(pixelRay, x, y, _voidColor);

			double red   = c.getRed();
			double green = c.getGreen();
			double blue  = c.getBlue();

			double local_max = std::max({red, green, blue});
			//double local_min = std::min({red, green, blue});

			max_brightnesses.push_back(local_max);

			image_copy[x][y][Bitmap::RED]   = red;
			image_copy[x][y][Bitmap::GREEN] = green;
			image_copy[x][y][Bitmap::BLUE]  = blue;
		}
	}

	std::sort(max_brightnesses.begin(),
	          max_brightnesses.end(),
	          [](double lhs,
	             double rhs) -> bool { return lhs < rhs; });

	uint32_t ninety_ninth =
		         ( static_cast<double>(max_brightnesses.size()) / 100 )
		         * 99;

	double max = max_brightnesses[ninety_ninth];

	double gamma = 0.4;

	for (uint16_t x = 0; x < _xRes; ++x) {
		for (uint16_t y = 0; y < _yRes; ++y) {

			Color adjusted = adjustColor(
				{
					image_copy[x][y][Bitmap::RED],
					image_copy[x][y][Bitmap::GREEN],
					image_copy[x][y][Bitmap::BLUE]
				}, max
			);

			image[x][y][Bitmap::RED] = static_cast<uint8_t>(
				255 * adjusted.getRed()
			);

			image[x][y][Bitmap::GREEN] = static_cast<uint8_t>(
				255 * adjusted.getGreen()
			);
			image[x][y][Bitmap::BLUE]  = static_cast<uint8_t>(
				255 * adjusted.getBlue()
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
	                      uint16_t y,
	                      Color voidColor) -> Color {
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

		Color objectColor;

		if (hits.empty()) {
			objectColor = voidColor;
		} else {

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

			objectColor = rt_math::phong(hit_point, hit_solid, ray.getDirection());
		}
		auto lights = LightSource::getLights();

		Color lightColor;

		while (!lights.empty()) {
			LightSource* ls = lights.front();
			lights.pop();

			// get distance of ray to light
			// brightness function: 2*(0.5 - d)

			double distance = ray.getMinDistanceTo(ls->getPoint());

			double brightness = 0.2 * ( 0.2 - distance );

			// XXX
			// lightColor += Color{rt_math::clamp(brightness, 0, 1)};

			// std::cout << brightness << "\n";
		}

		return objectColor + lightColor;
	});
}

const Color&
Camera::getVoidColor() const {
	return _voidColor;
}

void
Camera::setVoidColor(const Color voidColor) {
	_voidColor = voidColor;
}

//void
//Camera::setYRes(uint16_t yRes) {
//	_yRes = yRes;
//}
