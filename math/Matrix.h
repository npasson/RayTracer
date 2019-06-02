//
// Created by root on 30.05.2019.
//

#ifndef RAYTRACING_MATRIX_H
#define RAYTRACING_MATRIX_H


#include <cstdint>
#include <vector>
#include <ostream>
#include "Point.h"

class Matrix {
public:
	typedef std::vector<std::vector<double>> _t;

	Matrix() = delete;

	Matrix(
			uint8_t,
			uint8_t);

	Matrix(
			uint8_t,
			uint8_t,
			std::vector<std::vector<double>>&&);

	explicit Matrix(const std::vector<std::vector<double>>&&);

	Matrix
	operator*(const Matrix&) const;

	Matrix&
	operator=(std::vector<std::vector<double>>);

	friend std::ostream&
	operator<<(
			std::ostream&,
			Matrix);

private:
	std::vector<std::vector<double>> _data;

	const uint8_t _rows;
public:
	const std::vector<std::vector<double>>
	getData() const;

	const uint8_t
	getRows() const;

	const uint8_t
	getCols() const;

private:
	const uint8_t _cols;
};


#endif //RAYTRACING_MATRIX_H
