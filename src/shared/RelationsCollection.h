/*
 * RelationsCollection.h
 */

#ifndef SRC_SHARED_RELATIONSCOLLECTION_H_
#define SRC_SHARED_RELATIONSCOLLECTION_H_

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>

// <Query ID, Document IDs>
class RelationsCollection : public std::map<unsigned int, std::set<unsigned int>> {

public:
	bool load(std::string fileName);
};


#endif /* SRC_SHARED_RELATIONSCOLLECTION_H_ */
