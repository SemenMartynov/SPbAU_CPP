//============================================================================
// Name        : CW03-nanIterator
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : An iterator for a std::string, which doesn't show numbers.
//============================================================================

#include <cstdlib>
#include <iterator>
#include <iostream>

template<class T>
class nanIterator: public std::iterator<std::forward_iterator_tag,
		typename std::iterator_traits<typename T::iterator>::value_type>
{
public:
	nanIterator(typename T::iterator startIt, typename T::iterator endIt) :
			startIt(startIt), endIt(endIt)
	{
		if (isdigit(*startIt))
		{
			nextNan();
		}
	}

	nanIterator(typename T::iterator endIt) :
			startIt(endIt), endIt(endIt)
	{
	}

	bool operator==(const nanIterator &tmp)
	{
		return (startIt == tmp.startIt);
	}

	bool operator!=(const nanIterator &tmp)
	{
		return (startIt != tmp.startIt);
	}

	typename T::iterator& operator++()
	{
		return nextNan();
	}

	typename T::iterator operator++(int)
	{
		typename T::iterator tmp = startIt;
		nextNan();
		return tmp;
	}

	typename std::iterator_traits<typename T::iterator>::reference operator*()
	{
		return *startIt;
	}
private:
	typename T::iterator startIt;
	typename T::iterator endIt;
	typename T::iterator &nextNan()
	{
		startIt++;
		while (startIt != endIt && isdigit(*startIt))
		{
			startIt++;
		}
		return startIt;
	}
};

int main(int argc, char* argv[])
{
	std::string s = "aa44a";

	nanIterator<std::string> magic1(s.begin(), s.end());
	nanIterator<std::string> magic2(s.end());

	std::copy(magic1, magic2, std::ostreambuf_iterator<char>(std::cout));
	return EXIT_SUCCESS;
}
