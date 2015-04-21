/*
 * StopwordsCollection.h
 */

#ifndef SRC_SHARED_RELATIONSCOLLECTION_H
#define SRC_SHARED_RELATIONSCOLLECTION_H

#include <parallel/algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>

class StopwordsCollection : public std::set<std::string> {
public:
	bool load(std::string fileName);
};


#endif /* SRC_SHARED_RELATIONSCOLLECTION_H */
