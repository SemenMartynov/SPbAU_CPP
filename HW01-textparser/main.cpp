//============================================================================
// Name        : HW01-text-parser
// Author      : Semen Martynov
// Version     : 1
// Copyright   : The MIT license
// Description : The program receives the text file on input, modifies it
//               according to rules of the configuration file, and saves
//               output results in the new file.
//============================================================================

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "include/RuleCollector.h"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "usage: " << argv[0] << " input output" << std::endl;
		return EXIT_FAILURE;
	}

	std::ifstream input_buffer(argv[1], std::ios::in);
	//std::ifstream input_buffer("itext.txt", std::ios::in);
	std::ofstream output_buffer(argv[2], std::ios::out);
	//std::ofstream output_buffer("otext.txt", std::ios::out);
	std::string sentence;

	// ruleCollector contains a vector with rules for text modification.
	RuleCollector ruleCollector;
	ruleCollector.read();

	// We read sentences out of the file. Sentences are separated by points.
	while (std::getline(input_buffer, sentence, '.'))
	{
		// Let's return a dot.
		sentence += ".";
		// Each sentence passes the list of rules.
		ruleCollector.execute(sentence);
		// Result registers in the file.
		output_buffer << sentence;
	}

	return EXIT_SUCCESS;
}
