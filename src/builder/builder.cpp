/*
 * builder.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <tclap/CmdLine.h>

#include "CollectionParser.h"


int main(int argc, char const *argv[])
{
	try {

		// Parse command-line arguments
		TCLAP::CmdLine cmd("Reversed index builder", ' ', "1.0");
		TCLAP::ValueArg<std::string> collectionArg("c", "collection", "Specifies a custom collection file (default: ./docs/cran.all.1400).", false, "./docs/cran.all.1400", "string");
		TCLAP::ValueArg<std::string> stopwordsArg("s", "stopwords", "Specifies a custom stopwords file (default ./docs/stopwords.txt).", false, "./docs/stopwords.txt", "string");
		TCLAP::ValueArg<std::string> outputArg("o", "output", "Specifies an output file for the index (default: ./docs/index.oarchive)", false, "./docs/index.oarchive", "string");

		cmd.add(collectionArg);
		cmd.add(stopwordsArg);
		cmd.add(outputArg);
		cmd.parse(argc, argv);

		// Initialize the Collection Parser
		CollectionParser parser(collectionArg.getValue());

		// Read stopwords and provide the list to the parser
		std::cout << "Parsing stopwords... "; std::cout.flush();
		parser.loadStopwords(stopwordsArg.getValue());
		std::cout << "OK" << std::endl;

		// Parse collection
		std::cout << "Parsing collection... "; std::cout.flush();
		parser.parseCollection();
		std::cout << "OK" << std::endl;
		std::cout << "Statistics: " << parser.getCollection().docs.size() << " documents and ";
		std::cout << parser.getCollection().terms.size() << " unique terms." << endl;

		// Save collection to a file
		std::cout << "Saving index... "; std::cout.flush();
		parser.getCollection().save(outputArg.getValue());
		std::cout << "OK" << std::endl;

	} catch (TCLAP::ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}


