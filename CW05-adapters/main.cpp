//============================================================================
// Name        : CW05-adapters
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : It is required to implement the functional adapters ptr_fun
//               (from the pointer on function) and bind (bind_1st, bind_2nd).
//============================================================================

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "includes/bind.h"
#include "includes/ptr_fun.h"

template<typename T>
void addOne(T& tmp)
{
	tmp += 1;
}

template<typename T>
void addOneIfLess(T& lhs, T& rhs)
{
	if (lhs < rhs)
	{
		lhs += 1;
	}
}

void showIfLessP(int lhs, int rhs)
{
	if (lhs < rhs)
	{
		std::cout << lhs << " ";
	}
}

int main(void)
{
	srand(time(NULL));

	std::vector<int> vv;

	for (int i = 0; i != 10; ++i)
	{
		vv.push_back(rand() % 100 + 1);
	}

	std::cout << "Vector: " << std::endl;
	std::copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl
			<< "Vector after addOne: "
			<< std::endl;
	std::for_each(vv.begin(), vv.end(), ::ptr_fun(addOne<int>));
	std::copy(vv.begin(), vv.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl
			<< "Let's print everyones, who less than the first."
			<< std::endl;
	std::for_each(vv.begin(), vv.end(), ::bind_2nd(::ptr_fun(&showIfLessP), *(vv.begin())));

	return EXIT_SUCCESS;
}
