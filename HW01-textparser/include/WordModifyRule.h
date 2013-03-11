/*
 * WordModifyRule.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef WORDMODIFYRULE_H_
#define WORDMODIFYRULE_H_

#include <algorithm>
#include "Rule.h"

// Class implements the substitution of one line to another. If the second string is not specified - the first is removed.
class WordModifyRule: public Rule
{
public:
	WordModifyRule(const std::string &first, const std::string &second = "") :
			Rule(first), second(second)
	{
	}
	void execute(std::string& tmp)
	{
		// In a line of the text we look for the word which needs to be replaced.
		std::string::iterator match = tmp.begin();
		while ((match = std::search(match, tmp.end(), first.begin(),
				first.end(), lower_test())) != tmp.end())
		{
			// check for whole word - the word must be at the beginning of a line, or after a space, and after it there shan't be letters.
			if ((match == tmp.begin() || *(match - 1) == ' ')
					&& !isalpha(match + first.length()))
			{
				// If the second word is, realizes changeover.
				if (second.length())
				{
					tmp.replace(match, match + first.length(), second);
					match += first.length();
				}
				// Otherwise - we delete the word.
				else
				{
					tmp.erase(match, match + first.length());
					//remove double spaces
					if (match != tmp.begin() && *(match - 1) == ' ')
					{
						tmp.erase(match - 1, match);
					}
					else if (match != tmp.end() && *(match + 1) == ' ')
					{
						tmp.erase(match, match + 1);
					}
				}
			}
			else
			{
				// Continue to search on a smaller segment.
				match++;
			}
		}
	}
private:
	const std::string second;
};

#endif /* WORDMODIFYRULE_H_ */
