/*
 * RelationsCollection.cpp
 */

#include "RelationsCollection.h"

/**
 * Loads the collection of relations from a specified file.
 *
 * @param fileName The file name.
 */

bool RelationsCollection::load(std::string fileName) {

	int query, doc, code;
	std::ifstream f(fileName);

	if(!f) {
		std::cerr << "Error opening " << fileName << "." << std::endl;
		return false;
	}

	while (f >> query >> doc >> code) (*this)[query].insert(doc);

	f.close();
	return true;
}

