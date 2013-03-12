/*
 * ptr_fun.h
 *
 *  Created on: 12 Mar 2013
 *      Author: Semen A Martynov
 */

#ifndef PTR_FUN_H_
#define PTR_FUN_H_

template<typename retType, typename arg>
class Cptr_fun
{
public:
	Cptr_fun(retType (*someFunc)(arg)) :
			storedFunc(someFunc)
	{
	}
	retType operator()(arg lhs)
	{
		return storedFunc(lhs);
	}
private:
	retType (*storedFunc)(arg);
};

template<typename retType, typename arg1, typename arg2>
class Cptr_fun2
{
public:

	typedef arg1 argument1Type;
	typedef arg2 argument2Type;
	typedef retType returnType;

	Cptr_fun2(retType (*someFunc)(arg1, arg2)) :
			storedFunc(someFunc)
	{
	}
	retType operator()(arg1 lhs, arg2 rhs)
	{
		return storedFunc(lhs, rhs);
	}
private:
	retType (*storedFunc)(arg1, arg2);
};

template<typename retType, typename arg>
Cptr_fun<retType, arg> ptr_fun(retType (*f)(arg))
{
	return Cptr_fun<retType, arg>(f);
}

template<typename retType, typename arg1, typename arg2>
Cptr_fun2<retType, arg1, arg2> ptr_fun(retType (*f)(arg1, arg2))
{
	return Cptr_fun2<retType, arg1, arg2>(f);
}

#endif /* PTR_FUN_H_ */
