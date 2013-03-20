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
	~Matrix();
	size_t getSize() const;
	Matrix& operator=(const Matrix&);
	const ProxyRow operator[](size_t row) const;
private:
	size_t size;
	T** matrix;
};

template<typename T>
Matrix<T>::Matrix(size_t size)
try :
		size(size), matrix(new T*[size])
{
	for (size_t i = 0; i != size; ++i)
	{
		matrix[i] = new T[size];
	}
}
catch (std::bad_alloc& ba)
{
	this->~Matrix();
	throw CException("Out of memory - operation is cancelled.");
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
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& tmp)
{
	if (this == &tmp)
	{
		return *this;
	}

	if (this)
	{
		this->~Matrix();
	}

	try
	{
		size = tmp.getSize();
		matrix = new T*[size];
		for (size_t i = 0; i != size; ++i)
		{
			matrix[i] = new T[size];
			for (size_t j = 0; j != size; ++j)
			{
				matrix[i][j] = tmp[i][j];
			}
		}
		return *this;
	} catch (std::bad_alloc& ba)
	{
		this->~Matrix();
		throw CException("Out of memory - operation is cancelled.");
	}
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

#endif /* MATRIX_H_ */
