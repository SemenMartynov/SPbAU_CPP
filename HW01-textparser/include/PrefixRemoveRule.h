/*
 * PrefixRemoveRule.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef PREFIXREMOVERULE_H_
#define PREFIXREMOVERULE_H_

#include "Rule.h"

class PrefixRemoveRule: public Rule
{
public:
	PrefixRemoveRule(const std::string &first) :
			Rule(first)
	{
	}
	void execute(std::string& tmp)
	{
		// Let's find substring entrance in a sentence from the file.
		std::string::iterator match = std::search(tmp.begin(), tmp.end(),
				first.begin(), first.end(), lower_test());
		// If it is found nothing, or it not a prefix
		if (match == tmp.end() || !isalpha(match + first.length()))
		{
			return;
		}

		// The sentence shall begin with the required prefix.
		std::string::iterator sentenceBegin = tmp.begin();
		while (sentenceBegin != match)
		{
			if (isalpha(sentenceBegin))
			{
				return;
			}
			sentenceBegin++;
		}

		// If at the beginning of a sentence there were control characters, it is good to save them.
		std::string::iterator cntrl = tmp.begin();
		while (cntrl != tmp.end())
		{
			if (!iscntrl(cntrl))
			{
				tmp.erase(cntrl, tmp.end());
				return;
			}
			cntrl++;
		}
	}
};

#endif /* PREFIXREMOVERULE_H_ */
