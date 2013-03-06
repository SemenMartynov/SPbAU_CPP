/*
 * random_shuffle.h
 *
 *  Created on: 6 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef RANDOM_SHUFFLE_H_
#define RANDOM_SHUFFLE_H_
#include <cstdlib>
#include <ctime>
#include <algorithm>

template<typename It>
void random_shuffle(It first, It last)
{
	// initialize random
	srand(time(NULL));

	size_t len = std::distance(first, last);
	It lhs = first;

	while (lhs != last)
	{
		It rhs = first;
		std::advance(rhs, rand() % len);
		std::iter_swap(lhs++, rhs);
	}
}

#endif /* RANDOM_SHUFFLE_H_ */
