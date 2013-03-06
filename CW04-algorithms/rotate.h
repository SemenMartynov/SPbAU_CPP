/*
 * rotate.h
 *
 *  Created on: 6 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef ROTATE_H_
#define ROTATE_H_
#include <algorithm>

template<typename It>
void rotate(It first, It some, It last)
{
	It tmp = some;
	while (first != tmp)
	{
		// Race
		std::iter_swap(first++, tmp++);
		// Reduce the distance.
		if (tmp == last)
		{
			tmp = some;
		} // New round
		else if (first == some)
		{
			some = tmp;
		}
	}
}
/*
 //__rotate(first, some, last, typename std::iterator_traits<It>::iterator_category());

 template<typename BidirectionalIt>
 void __rotate(BidirectionalIt first, BidirectionalIt some, BidirectionalIt last,
 bidirectional_iterator_tag)
 {
 BidirectionalIt preLast = last;
 preLast--;
 while (some != preLast)
 {
 std::iter_swap(first++, some++);
 }
 while (first != some)
 {
 std::iter_swap(first++, some);
 }
 }

 template<typename RandomAccessIt>
 void __rotate<>(RandomAccessIt first, RandomAccessIt some, RandomAccessIt last,
 random_access_iterator_tag)
 {
 while (some + 1 != last)
 {
 std::iter_swap(first++, some++);
 }
 while (first != some)
 {
 std::iter_swap(first++, some);
 }
 }
 */
#endif /* ROTATE_H_ */
