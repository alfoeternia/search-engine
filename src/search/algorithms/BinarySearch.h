/*
 * BinarySearch.h
 */

#ifndef SRC_BINARYSEARCH_H_
#define SRC_BINARYSEARCH_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
#include <map>
#include <string>
using std::string;

#include "../../shared/Collection.h"
#include "BinaryQueryParser.h"

class BinarySearch {
private:
	Collection c;

public:
	BinarySearch();
	virtual ~BinarySearch();


	bool loadCollection(std::string fileName);
	bool processQuery(std::string q);
};

#endif /* SRC_BINARYSEARCH_H_ */
