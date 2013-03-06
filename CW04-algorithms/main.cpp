//============================================================================
// Name        : CW04-algorithms
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : std::rotate, std::reverse and std::random_shuffle algorithms
//               implementation for RandomAccessIterator and ForwardIterator
//============================================================================

#include <cstdlib>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>

#include "reverse.h"
#include "rotate.h"
#include "random_shuffle.h"

int main(void)
{

	std::vector<int> v;
	std::list<int> l;
	for (int i = 0; i != 10; ++i)
	{
		v.push_back(i);
		l.push_back(i);
	}

	std::cout << "Vector:" << std::endl;
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "reverse:" << std::endl;
	::reverse(v.begin(), v.end());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "rotate:" << std::endl;
	::rotate(v.begin(), v.begin() + 3, v.end());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "random shuffle:" << std::endl;
	::random_shuffle(v.begin(), v.end());
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << std::endl << "List:" << std::endl;
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "reverse:" << std::endl;
	::reverse(l.begin(), l.end());
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "rotate:" << std::endl;
	std::list<int>::iterator shift = l.begin();
	std::advance(shift, 3);
	::rotate(l.begin(), shift, l.end());
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "random shuffle:" << std::endl;
	::random_shuffle(l.begin(), l.end());
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));

	return EXIT_SUCCESS;
}
