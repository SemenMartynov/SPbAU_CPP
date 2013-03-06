/*
 * reverse.h
 *
 *  Created on: 6 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef REVERSE_H_
#define REVERSE_H_
#include <algorithm>

template<typename It>
void reverse(It first, It last)
{
	while (first != last && first != --last)
	{
		std::iter_swap(first, last);
		first++;
	}
}

#endif /* REVERSE_H_ */
