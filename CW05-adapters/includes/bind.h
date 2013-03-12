/*
 * bind.h
 *
 *  Created on: 12 Mar 2013
 *      Author: Semen A Martynov
 */

#ifndef BIND_H_
#define BIND_H_

#include "ptr_fun.h"

template<typename func>
class Cbind_2nd
{
protected:
	func storedFunc;
	typename func::argument2Type second;
public:
	Cbind_2nd(const func& someFunc, const typename func::argument2Type& tmp) :
			storedFunc(someFunc), second(tmp)
	{
	}
	typename func::returnType operator()(
			typename func::argument1Type& first)
	{
		return storedFunc(first, second);
	}
};

template<typename func>
class Cbind_1st
{
protected:
	func storedFunc;
	typename func::argument1Type first;
public:
	Cbind_1st(const func& someFunc, const typename func::argument1Type& tmp) :
			storedFunc(someFunc), first(tmp)
	{
	}
	typename func::returnType operator()(
			typename func::argument2Type& second)
	{
		return storedFunc(first, second);
	}
};

template<typename func, typename argType>
Cbind_2nd<func> bind_2nd(const func& someFunc, const argType& second)
{
	return Cbind_2nd<func>(someFunc, typename func::argument2Type(second));
}

template<typename func, typename argType>
Cbind_1st<func> bind_1st(const func& someFunc, const argType& first)
{
	return Cbind_1st<func>(someFunc, typename func::argument1Type(first));
}

#endif /* BIND_H_ */
