/*
 * Collection.cpp
 */

#include "Collection.h"

Collection::Collection() {}
Collection::~Collection() {}

/**
 * Restores the collection from a specified file using boost::serialization.
 *
 * @param fileName The file name.
 * @see http://www.boost.org/doc/libs/1_58_0/libs/serialization/doc/index.html
 */
bool Collection::save(std::string fileName) {
	std::ofstream f(fileName);
	if(!f) {
			std::cerr << "Error opening " << fileName << "." << std::endl;
			return false;
		}

	boost::archive::text_oarchive oa(f);
	oa << *this;
	f.close();
	return true;
}

/**
 * Saves the collection to a specified file using boost::serialization.
 *
 * @param fileName The file name
 * @see http://www.boost.org/doc/libs/1_58_0/libs/serialization/doc/index.html
 */
bool Collection::load(std::string fileName) {
	// Open archive file
	std::ifstream f(fileName);
	if(!f) {
		std::cerr << "Error opening " << fileName << "." << std::endl;
		return false;
	}

	// Read archive file and populate collection
	boost::archive::text_iarchive oi(f);
	oi >> *this;
	f.close();

	return true;
}

