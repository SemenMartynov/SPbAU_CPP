/*
 * CException.h
 *
 *  Created on: 19 Mar 2013
 *      Author: Semen A Martynov
 */

#ifndef CEXCEPTION_H_
#define CEXCEPTION_H_

#include <exception>
#include <string>

class CException: public std::exception
{
public:
	CException(const std::string& message) :
			message(message)
	{
	}
	virtual ~CException() throw ()
	{
	}
	virtual const char* what() const throw ()
	{
		return message.c_str();
	}
private:
	std::string message;
};
#endif /* CEXCEPTION_H_ */
