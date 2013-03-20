//============================================================================
// Name        : CW06-Matrix
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : Demonstration operations with exceptions with a matrix class.
//============================================================================

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "includes/Matrix.h"

template<typename T>
void showMatrix(Matrix<T>& matrix)
{
	for (size_t i = 0; i != matrix.getSize(); ++i)
	{
		for (size_t j = 0; j != matrix.getSize(); ++j)
		{
			std::cout << std::setw(3) << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

template<typename T>
void fillMatrix(Matrix<T>& matrix)
{
	srand(time(NULL));
	for (size_t i = 0; i != matrix.getSize(); ++i)
	{
		for (size_t j = 0; j != matrix.getSize(); ++j)
		{
			matrix[i][j] = rand() % 100;
		}
	}
}

int main(void)
{

	try
	{
		std::cout << "The first matrix:" << std::endl;
		Matrix<int> matrix1(5);
		fillMatrix(matrix1);
		showMatrix(matrix1);

		std::cout << "\nThe second matrix:" << std::endl;
		Matrix<int> matrix2(10);
		fillMatrix(matrix2);
		showMatrix(matrix2);
		matrix2[11][1] = 2;

		std::cout << "\nMove 2nd to 1st:" << std::endl;
		matrix1 = matrix2;
		showMatrix(matrix1);

		std::cout << "\nThe matrix:" << std::endl;
		Matrix<double> matrix3(10);
		fillMatrix(matrix3);
		showMatrix(matrix3);
	} catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	} catch (const CException& ce)
	{
		std::cerr << ce.what() << '\n';
	}
	return EXIT_SUCCESS;
}
