/*
 * Matrix.h
 *
 *  Created on: 19 Mar 2013
 *      Author: Semen A Martynov
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <stdexcept>
#include <algorithm>
#include "CException.h"

template<typename T>
class Matrix
{
private:
	class ProxyRow
	{
	public:
		ProxyRow(size_t size, T* row) :
				size(size), row(row)
		{
		}
		T& operator[](size_t col) const
		{
			if (col >= size || col < 0)
			{
				throw std::out_of_range("col number in incorrect!");
			}
			return row[col];
		}
	private:
		const size_t size;
		T* const row;
	};

public:
	Matrix(size_t size);
	Matrix(const Matrix<T>&);
	~Matrix();
	size_t getSize() const;
	Matrix& operator=(const Matrix<T>&);
	const ProxyRow operator[](size_t row) const;
private:
	size_t size;
	T** matrix;
	void swap(Matrix<T>&); //copy-and-swap
};

template<typename T>
Matrix<T>::Matrix(size_t size) :
		size(size), matrix(0)
{
	try
	{
		matrix = new T*[size];

		for (size_t i = 0; i != size; ++i)
		{
			matrix[i] = 0;
		}

		for (size_t i = 0; i != size; ++i)
		{
			matrix[i] = new T[size];
		}

	} catch (std::exception const& e)
	{
		if (matrix)
		{
			for (size_t k = 0; k != size; ++k)
				if (matrix[k])
				{
					delete[] matrix[k];
				}
			delete[] matrix;
		}

		throw CException("Constructor is cancelled: " + e.what());
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& otherMatrix) :
		size(otherMatrix.getSize()), matrix(0)
{
	try
	{
		matrix = new T*[size];

		for (size_t i = 0; i != size; ++i)
		{
			matrix[i] = 0;
		}

		for (size_t i = 0; i != size; ++i)
		{
			matrix[i] = new T[size];
		}

		for (size_t i = 0; i != size; ++i)
		{
			for (size_t j = 0; j != size; ++j)
			{
				matrix[i][j] = otherMatrix[i][j];
			}
		}
	} catch (std::exception const& e)
	{
		if (matrix)
		{
			for (size_t k = 0; k != size; ++k)
				if (matrix[k])
				{
					delete[] matrix[k];
				}
			delete[] matrix;
		}

		throw CException("Copy constructor is cancelled: " + e.what());
	}
}

template<typename T>
Matrix<T>::~Matrix()
{
	if (matrix)
	{
		for (size_t i = 0; i != size; ++i)
		{
			if (matrix[i])
			{
				delete[] matrix[i];
			}
		}
		delete[] matrix;
	}
	size = 0;
}

template<typename T>
inline size_t Matrix<T>::getSize() const
{
	return size;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& otherMatrix)
{
	Matrix tmp(otherMatrix);
	swap(tmp);
	return *this;
}

template<typename T>
const typename Matrix<T>::ProxyRow Matrix<T>::operator[](size_t row) const
{
	if (row >= size || row < 0)
	{
		throw std::out_of_range("row number in incorrect!");
	}
	return ProxyRow(size, matrix[row]);
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& otherMatrix)
{
	std::swap(size, otherMatrix.size);
	std::swap(matrix, otherMatrix.matrix);
}

#endif /* MATRIX_H_ */
