//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <ostream>

class Color {
	double _red;
public:
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

private:
	double _green;
	double _blue;
public:
	Color();

	explicit Color(double brightness);

	Color(double r,
	      double g,
	      double b);

	double
	getBrightness();

	Color
	operator*(double rhs) const;

	Color
	operator/(double rhs) const;

	friend std::ostream&
	operator<<(std::ostream&,
	           Color);
};

#endif //RAYTRACING_COLOR_H
