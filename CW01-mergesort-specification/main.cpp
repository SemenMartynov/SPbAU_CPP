//============================================================================
// Name        : CW01-mergesort-specification
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : Merge sort algorithm specification for std::list
//============================================================================

#include <cstdlib>
#include <vector>
#include <list>
#include <iterator>
#include <iostream>

template<class T>
T merge(const T &lhs, const T &rhs)
{
	T mrgdResult;
	size_t lhsIndex = 0;
	size_t rhsIndex = 0;

	while (lhsIndex < lhs.size() && rhsIndex < rhs.size())
	{
		if (lhs[lhsIndex] < rhs[rhsIndex])
		{
			mrgdResult.push_back(lhs[lhsIndex]);
			lhsIndex++;
		}
		else
		{
			mrgdResult.push_back(rhs[rhsIndex]);
			rhsIndex++;
		}
	}

	while (lhsIndex < lhs.size())
	{
		mrgdResult.push_back(lhs[lhsIndex]);
		lhsIndex++;
	}

	while (rhsIndex < rhs.size())
	{
		mrgdResult.push_back(rhs[rhsIndex]);
		rhsIndex++;
	}

	return mrgdResult;
}

template<class U>
std::list<U> merge(const std::list<U> &lhs, const std::list<U> &rhs)
{
	std::list<U> mrgdResult;

	typename std::list<U>::const_iterator lhsIt = lhs.begin();
	typename std::list<U>::const_iterator rhsIt = rhs.begin();

	while (lhsIt != lhs.end() && rhsIt != rhs.end())
	{
		if (*lhsIt < *rhsIt)
		{
			mrgdResult.push_back(*lhsIt);
			lhsIt++;
		}
		else
		{
			mrgdResult.push_back(*rhsIt);
			rhsIt++;
		}
	}
	while (lhsIt != lhs.end())
	{
		mrgdResult.push_back(*lhsIt);
		lhsIt++;

	}
	while (rhsIt != rhs.end())
	{
		mrgdResult.push_back(*rhsIt);
		rhsIt++;
	}

	return mrgdResult;
}

template<class T>
T mergeSort(T &tmp)
{
	if (tmp.size() == 1)
	{
		return tmp;
	}

	typename T::iterator mediana = tmp.begin();
	std::advance(mediana, tmp.size() / 2);

	T lhs(tmp.begin(), mediana);
	T rhs(mediana, tmp.end());

	lhs = mergeSort(lhs);
	rhs = mergeSort(rhs);

	return merge(lhs, rhs);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	std::vector<int> unsortedVec;
	std::list<double> unsortedList;

	for (int i = 0; i != 10; ++i)
	{
		unsortedVec.push_back(rand() % 100 + 1);
		unsortedList.push_back((double)rand() / RAND_MAX + 1);
	}

	std::vector<int> sortedVec = mergeSort(unsortedVec);
	std::list<double> sortedList = mergeSort(unsortedList);

	std::cout << "Unsorted vector:" << std::endl;
	std::copy(unsortedVec.begin(), unsortedVec.end(),std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl << "Sorted vector:" << std::endl;
	std::copy(sortedVec.begin(), sortedVec.end(),std::ostream_iterator<int>(std::cout, " "));

	std::cout << std::endl << "Unsorted list:" << std::endl;
	std::copy(unsortedList.begin(), unsortedList.end(),
			std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl << "Sorted list:" << std::endl;
	std::copy(sortedList.begin(), sortedList.end(),
			std::ostream_iterator<double>(std::cout, " "));

	return EXIT_SUCCESS;
}
