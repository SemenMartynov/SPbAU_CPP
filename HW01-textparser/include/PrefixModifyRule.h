/*
 * PrefixModifyRule.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef PREFIXMODIFYRULE_H_
#define PREFIXMODIFYRULE_H_

#include "Rule.h"
#include <cstdlib>


class PrefixModifyRule: public Rule
{
public:
	PrefixModifyRule(const std::string &first, const std::string &second = "") :
			Rule(first), second(second)
	{
	}
	void execute(std::string& tmp)
	{
		// In a line of the text we look for the prefix which needs to be replaced.
		std::string::iterator match = tmp.begin();
		while ((match = std::search(match, tmp.end(), first.begin(),
				first.end(), lower_test())) != tmp.end())
		{
			// check for prefix - begins with the beginning of a line (or costs after a gap), but after it there shall be other letters.
			if ((match == tmp.begin() || *(match - 1) == ' ')
					&& isalpha(match + first.length()))
			{
				// If the second prefix is, realizes changeover.
				if (second.length())
				{
					tmp.replace(match, match + first.length(), second);
					match += first.length();
				}
				// Otherwise - we delete the word to space
				else
				{
					std::string::iterator wordEnd = match;
					// To find the nearest space will move by UTF-8 characters.
					while (wordEnd != tmp.end() && isalpha(wordEnd))
					{
						std::string::difference_type offset = 1;
						if (*wordEnd & firstMask)
						{
							if (*wordEnd & thirdMask)
							{
								if (*wordEnd & fourthMask)
									offset = 4;
								else
									offset = 3;
							}
							else
							{
								offset = 2;
							}
						}
						wordEnd += offset;
					}
					tmp.erase(match, wordEnd);
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

#endif /* PREFIXMODIFYRULE_H_ */
