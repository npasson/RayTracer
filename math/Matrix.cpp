//
// Created by root on 30.05.2019.
//

#include "Matrix.h"

Matrix::Matrix(
		uint8_t rows,
		uint8_t cols)
		: _rows(rows),
		  _cols(cols) {
	this->_data = std::vector<std::vector<double>>(rows, std::vector<double>(cols));
}

Matrix::Matrix(
		uint8_t rows,
		uint8_t cols,
		std::vector<std::vector<double>>&& data)
		: _rows(rows),
		  _cols(cols) {
	this->_data = data;
}

std::vector<std::vector<double>>
Matrix::getData() const {
	return _data;
}

uint8_t
Matrix::getRows() const {
	return _rows;
}

uint8_t
Matrix::getCols() const {
	return _cols;
}

Matrix
Matrix::operator*(const Matrix& rhs) const {
	if (this->_cols != rhs._rows) {
		return Matrix(this->_rows, rhs._cols);
	}

	Matrix m = Matrix(this->_rows, rhs._cols);

	for (uint8_t row = 0; row < this->_rows; ++row) {
		for (uint8_t col = 0; col < rhs._cols; ++col) {
			for (uint8_t i = 0; i < this->_cols; ++i) {
				m._data[row][col]
						+= ( this->_data[row][i] )
						   * ( rhs._data[i][col] );
			}
		}
	}

	return m;
}

Matrix&
Matrix::operator=(std::vector<std::vector<double>> data) {
	if (data.size() == this->_rows
	    && data[0].size() == this->_cols) {
		this->_data = data;
	}

	return *this;
}

std::ostream&
operator<<(
		std::ostream& lhs,
		Matrix rhs) {
	lhs << "{";
	for (uint8_t row = 0; row < rhs._rows; ++row) {
		lhs << "{";
		for (uint8_t col = 0; col < rhs._cols; ++col) {
			lhs << rhs._data[row][col];
			if (col != ( rhs._cols - 1 )) {
				lhs << ",";
			}
		}
		lhs << "}";
		if (row != ( rhs._rows - 1 )) {
			lhs << ",";
		}
	}
	lhs << "}";
	return lhs;
}

Matrix::Matrix(const std::vector<std::vector<double>>&& data)
		: _rows(static_cast<uint8_t>(data.size())),
		  _cols{static_cast<uint8_t>(data.front()
		                                 .size())} {
	this->_data = data;
}

