/*
 * Rule.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef RULE_H_
#define RULE_H_

#include <algorithm>
#include <string>
#include <locale>

// The class describes the abstract rule
class Rule
{
public:
	Rule(const std::string &first) :
			first(first)
	{
	}
	virtual void execute(std::string&) = 0;
	virtual ~Rule()
	{
	}
protected:
	// All rules have at least one line
	const std::string first;
	// The functor for string comparison, without the register.
	struct lower_test
	{
		bool operator()(char lhs, char rhs) const
		{
			return (std::tolower(lhs) == std::tolower(rhs));
		}
	};
	// Set of masks for operation with UTF8
	static const unsigned char firstMask = 128; // 1000000
	static const unsigned char thirdMask = 32;  // 0010000
	static const unsigned char fourthMask = 16; // 0001000
	// UTF8 is a variable-width encoding, we need to know width of current symbol
	wchar_t getCharCode(std::string::const_iterator it) const
	{
		wchar_t charCode = 0;

		char firstByte = *it;

		if (firstByte & firstMask)
		{
			if (firstByte & thirdMask)
			{
				if (firstByte & fourthMask)
				{
					charCode = (firstByte & 0x07) << 18;
					char secondByte = *(it + 1);
					charCode += (secondByte & 0x3f) << 12;
					char thirdByte = *(it + 2);
					charCode += (thirdByte & 0x3f) << 6;
					char fourthByte = *(it + 3);
					charCode += (fourthByte & 0x3f);
				}
				else
				{
					charCode = (firstByte & 0x0f) << 12;
					char secondByte = *(it + 1);
					charCode += (secondByte & 0x3f) << 6;
					char thirdByte = *(it + 2);
					charCode += (thirdByte & 0x3f);
				}
			}
			else
			{
				charCode = (firstByte & 0x1f) << 6;
				char secondByte = *(it + 1);
				charCode += (secondByte & 0x3f);
			}
		}
		else
		{
			charCode = firstByte;
		}
		return charCode;
	}
	// Function checks, whether is the specified character a letter
	bool isalpha(std::string::const_iterator it) const
	{
		return std::isalpha(getCharCode(it), std::locale("ru_RU.UTF-8"));
	}
	// Function checks existence of the control character
	bool iscntrl(std::string::const_iterator it) const
	{
		return std::iscntrl(getCharCode(it), std::locale("ru_RU.UTF-8"));
	}
};

#endif /* RULE_H_ */
