/*
 * BinarySearch.cpp
 */

#include "BinarySearch.h"

BinarySearch::BinarySearch() {

}

BinarySearch::~BinarySearch() {

}

bool BinarySearch::loadCollection(std::string fileName) {

	// Open archive file
	std::ifstream f(fileName);
	if(!f) {
		cerr << "Error opening " << fileName << ". Exiting." << endl;
		return false;
	}

	// Read archive file and populate collection
	boost::archive::text_iarchive oi(f);
	oi >> c;
	f.close();

	return true;
}


bool processQuery(std::string q) {
	//BinaryQueryParser

	return true;
}
