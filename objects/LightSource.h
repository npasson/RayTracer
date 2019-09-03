//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_LIGHTSOURCE_H
#define RAYTRACING_LIGHTSOURCE_H

#include <queue>

#include "../math/Vec3.h"
#include "../math/Color.h"
#include "../math/Point.h"

class LightSource
	: public Point {

private:
	static std::queue<LightSource*> lights;
public:
	static const std::queue<LightSource*>&
	getLights();

	LightSource(const Point& location,
	            const Color& color,
	            double brightness);

	void
	setLocation(const Point& location);

	const Color&
	getColor() const;

	void
	setColor(const Color& color);

	double
	getBrightness() const;

	void
	setBrightness(double brightness);

private:
	Color  _color;
	double _brightness;
};

#endif //RAYTRACING_LIGHTSOURCE_H
