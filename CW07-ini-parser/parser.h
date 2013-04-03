/*
 * parser.h
 *
 *  Created on: 3 Apr 2013
 *      Author: sam
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::map;
using std::pair;
using std::runtime_error;

typedef map<string, string> attributes;
typedef map<string, attributes> iniData;

class Parser
{
public:
	Parser(const string& inputFile);
	//Parser(const Parser& otherParser);
	//Parser& operator=(const Parser& otherParser);

	string getString(const string& section, const string& key) const;
	int getInt(const string& section, const string& key) const;

	void setString(const string& section, const string& key, const string& val);
	void setInt(const string& section, const string& key, const int val);

	void write(const string& outputFile) const;

private:
	string &clean(string &str);
	string &ltrim(string &str);
	string &rtrim(string &str);
	string &trim(string &str);

	iniData data;
};

Parser::Parser(const string& inputFile)
{
	pair<iniData::iterator, bool> secResult;
	std::ifstream file(inputFile.c_str(), std::ifstream::in);

	if (file.fail())
		throw runtime_error("Can't open \"" + inputFile + "\" for reading");

	string buff;
	while (file)
	{
		getline(file, buff);
		buff = trim(clean(buff));

		if (!buff.empty())
		{
			if (buff[0] == '[' && buff[buff.length() - 1] == ']')
			{
				buff.erase(buff.begin(), buff.begin() + 1);
				buff.erase(buff.end() - 1, buff.end());
				if (buff == "")
					throw runtime_error("file is not in ini format");
				attributes a;
				secResult = data.insert(pair<string, attributes>(buff, a));
				//if (!secResult.second)
				//	throw runtime_error("An unknown error has occurred - can't get section " + buff);
			}
			else
			{
				size_t res = buff.find('=');
				if (res == string::npos)
					throw runtime_error("file is not in ini format");

				string key(buff.begin(), buff.begin() + res);
				string val(buff.begin() + res + 1, buff.end());
				pair<attributes::iterator, bool> atrResult =
						secResult.first->second.insert(
								pair<string, string>(trim(key), trim(val)));
				//if (!atrResult.second)
				//throw runtime_error("An unknown error has occurred - can't get attribute " + key + " = " + val);
			}
		}
	}
}

//Parser::Parser(const Parser& otherParser);

//Parser::Parser& operator=(const Parser& otherParser);

string Parser::getString(const string& section, const string& key) const
{
	iniData::const_iterator secIt = data.find(section);
	if (secIt == data.end())
	{
		throw runtime_error("Section " + section + " doesn't exist!");
	}

	attributes::const_iterator attIt = (secIt->second).find(key);
	if (attIt == (secIt->second).end())
	{
		throw runtime_error(
				"Attribute " + key + " on section " + section
						+ " doesn't exist!");
	}

	return attIt->second;
}

int Parser::getInt(const string& section, const string& key) const
{
	return std::stoi(getString(section, key)); // throws std::invalid_argument, std::out_of_range
}

void Parser::setString(const string& section, const string& key,
		const string& val)
{
	iniData::iterator secIt = data.find(section);
	if (secIt != data.end())
	{
		pair<iniData::iterator, bool> secResult;
		attributes a;
		secResult = data.insert(pair<string, attributes>(section, a));
		//if (!secResult.second)
		//	throw runtime_error("An unknown error has occurred - can't insert section " + section);
		secIt = secResult.first;
	}

	attributes::iterator attIt = (secIt->second).find(key);
	if (attIt == (secIt->second).end())
	{
		pair<attributes::iterator, bool> atrResult = secIt->second.insert(
				pair<string, string>(key, val));
		//if (!atrResult.second)
		//	throw runtime_error("An unknown error has occurred - can't insert attribute " + key + " on section " + section);
	}
	else
	{
		attIt->second = val;
	}
}

void Parser::setInt(const string& section, const string& key, const int val)
{
	setString(section, key, std::to_string(val));
}

void Parser::write(const string& outputFile) const
{
	std::ofstream file(outputFile.c_str());

	if (!file)
		throw runtime_error("Can't open \"" + outputFile + "\" for writing");

	for (iniData::const_iterator secIt = data.begin(); secIt != data.end();
			++secIt)
	{
		file << "[" << secIt->first << "]" << std::endl;

		for (attributes::const_iterator attIt = (secIt->second).begin();
				attIt != (secIt->second).end(); ++attIt)
		{
			file << attIt->first << "=" << attIt->second << std::endl;
		}
	}
}

string &Parser::clean(string &str)
{
	size_t res = str.find(';');
	if (res == string::npos)
		return str;
	str.erase(str.begin() + res, str.end());
	return str;
}

string &Parser::ltrim(string &str)
{
	str.erase(str.begin(),
			std::find_if(str.begin(), str.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
	return str;
}

string &Parser::rtrim(string &str)
{
	str.erase(
			std::find_if(str.rbegin(), str.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			str.end());
	return str;
}

string &Parser::trim(string &str)
{
	return ltrim(rtrim(str));
}

#endif /* PARSER_H_ */
