//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <ostream>
#include <vector>
#include "../generic/defines.h"

class Color {
	double _red;
	double _green;
	double _blue;
public:
	Color();

	explicit Color(double brightness);

	Color(double r,
	      double g,
	      double b);

	double
	getRed() const;

	void
	setRed(double red);

	double
	getGreen() const;

	void
	setGreen(double green);

	double
	getBlue() const;

	void
	setBlue(double blue);

	double
	getBrightness();

	static byte_t
	toByte(double);

	static Color
	combine(const std::vector<Color>&);

	Color
	operator*(double rhs) const;

	Color
	operator/(double rhs) const;

	friend std::ostream&
	operator<<(std::ostream&,
	           Color);
};

#endif //RAYTRACING_COLOR_H
