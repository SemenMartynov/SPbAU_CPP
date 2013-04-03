//============================================================================
// Name        : CW07-ini-parser
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : Implementation of ini parcer with warranties of exceptions.
//============================================================================

#include <cstdlib>
#include <iostream>
#include "parser.h"

int main(void)
{
	try
	{
		Parser parser("example.ini");
		std::cout << parser.getString("Section1", "var1") << std::endl;
		std::cout << parser.getString("Section2", "var2") << std::endl;
		std::cout << parser.getInt("Section1", "var2") << std::endl;
		parser.setString("Section3", "var3", "test");
		std::cout << parser.getString("Section3", "var3") << std::endl;
		parser.setInt("Section3", "var3", 7);
		std::cout << parser.getString("Section3", "var3") << std::endl;
		return EXIT_SUCCESS;
	} catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
