/*
 * RelationsCollection.cpp
 */

#include "StopwordsCollection.h"

/**
 * Loads the collection of stopwords from a specified file.
 *
 * @param fileName The file name.
 */

bool StopwordsCollection::load(std::string fileName) {

	// Read stopwords and provide the list to the parser
	std::ifstream f(fileName);
	if(!f) {
		std::cerr << "Error opening stopwords file." << std::endl << "Exiting." << std::endl;
		return -1;
	}
	std::copy(std::istream_iterator<std::string>(f), std::istream_iterator<std::string>(), inserter(*this, this->begin()));

	f.close();

	return true;
}

