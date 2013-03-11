/*
 * RuleCollector.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef RULECOLLECTOR_H_
#define RULECOLLECTOR_H_

#include <vector>
#include "Rule.h"
#include "PrefixModifyRule.h"
#include "PrefixRemoveRule.h"
#include "WordModifyRule.h"
#include "WordRemoveRule.h"

class RuleCollector
{
public:
	// Function reads rules from the configuration file, and saves them in a vector.
	void read(const char* codePath = "rules.cfg")
	{
		std::ifstream input_buffer(codePath, std::ios::in);

		std::string first;
		std::string second;
		std::string third;
		std::string fourth;

		while (input_buffer >> first >> second >> third >> fourth)
		{
			if (!first.compare("word"))
			{
				if (!third.compare("replace"))
				{
					rules.push_back(new WordModifyRule(second, fourth));
				}
				else if (!third.compare("remove"))
				{
					if (!fourth.compare("word"))
					{
						rules.push_back(new WordModifyRule(second));
					}
					else if (!fourth.compare("sentence"))
					{
						rules.push_back(new WordRemoveRule(second));
					}
					else
					{
						std::cerr << "Syntax error! Can't understand " + fourth
								<< std::endl;
					}
				}
				else
				{
					std::cerr << "Syntax error! Can't understand " + third
							<< std::endl;
				}
			}
			else if (!first.compare("prefix"))
			{
				if (!third.compare("replace"))
				{
					rules.push_back(new PrefixModifyRule(second, fourth));
				}
				else if (!third.compare("remove"))
				{
					if (!fourth.compare("word"))
					{
						rules.push_back(new PrefixModifyRule(second));
					}
					else if (!fourth.compare("sentence"))
					{
						rules.push_back(new PrefixRemoveRule(second));
					}
					else
					{
						std::cerr << "Syntax error! Can't understand " + fourth
								<< std::endl;
					}
				}
				else
				{
					std::cerr << "Syntax error! Can't understand " + third
							<< std::endl;
				}
			}
			else
			{
				std::cerr << "Syntax error! Can't understand " + first
						<< std::endl;
			}
		}
	}
	// The string is processed by ALL rules (in order of reading rules)
	void execute(std::string& tmp)
	{
		for (std::vector<Rule *>::iterator it = rules.begin();
				it != rules.end(); ++it)
		{
			(*it)->execute(tmp);
		}
	}

private:
	std::vector<Rule *> rules;
};

#endif /* RULECOLLECTOR_H_ */
