//============================================================================
// Name        : CW05-Expat
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : It is required to download RSS feed and parse it using expat library.
//============================================================================

#include <expat.h>
#include <cstring>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

std::multimap<std::string, std::string> newsCollector;
struct ReadedData
{
	ReadedData() :
			fItem(false), fTitle(false), fCategory(false)
	{
	}
	bool fItem;
	bool fTitle;
	bool fCategory;
	std::string title;
	std::string category;
} readedData;

void XMLCALL start_element(void *data, const char *element,
		const char **attribute)
{
	if (strcmp("item", element) == 0)
	{
		readedData.fItem = true;
	}
	else if (strcmp("title", element) == 0)
	{
		readedData.fTitle = true;
	}
	else if (strcmp("category", element) == 0)
	{
		readedData.fCategory = true;
	}
}

void XMLCALL end_element(void *data, const char *el)
{
	if (strcmp("item", el) == 0)
	{
		if (!readedData.title.empty() && !readedData.category.empty())
		{
			newsCollector.insert(
					std::pair<std::string, std::string>(readedData.category,
							readedData.title));
		}
		readedData.title.clear();
		readedData.category.clear();
		readedData.fItem = false;
	}
}

void XMLCALL handle_data(void *data, const char *content, int length)
{
	if (readedData.fItem)
	{
		if (readedData.fTitle)
		{
			readedData.title.assign(content, content + length);
			readedData.fTitle = false;
		}
		else if (readedData.fCategory)
		{
			readedData.category.assign(content, content + length);
			readedData.fCategory = false;
		}
	}
}

int main(int argc, char **argv)
{
	std::ifstream input_buffer("yandexfull.rss", std::ios::in | std::ios::ate);
	size_t size = input_buffer.tellg();
	char* data = new char[size + 1];
	input_buffer.seekg(0, std::ios::beg);
	/* prepare parser */
	XML_Parser parser = XML_ParserCreate("UTF-8");
	XML_SetElementHandler(parser, start_element, end_element);
	XML_SetCharacterDataHandler(parser, handle_data);
	/* parse the xml */
	input_buffer.read(data, size);
	if (XML_Parse(parser, data, size, input_buffer.eof()) == XML_STATUS_ERROR)
	{
		std::cout << "Error: " << XML_ErrorString(XML_GetErrorCode(parser))
				<< std::endl;
	}
	/* clean up */
	XML_ParserFree(parser);
	delete[] data;
	/* print results */
	for (std::multimap<std::string, std::string>::iterator it =
			newsCollector.begin(); it != newsCollector.end(); ++it)
	{
		std::cout << (*it).first << "  ==  " << (*it).second << std::endl;
	}

	return EXIT_SUCCESS;
}
