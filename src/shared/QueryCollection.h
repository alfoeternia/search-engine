/*
 * QueryCollection.h
 */

#ifndef SHARED_QUERYCOLLECTION_H_
#define SHARED_QUERYCOLLECTION_H_

#include <parallel/algorithm>
#include <boost/algorithm/string.hpp>
#include <cstdlib>
#include <cstring>
using std::string;
#include <fstream>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <list>
using std::list;
#include <string>
#include <map>
#include <set>
#include <vector>

#include "StopwordsCollection.h"
#include "../lib/porter2_stemmer.h"

struct QueryItem {
	unsigned int id;
	std::string text;
	std::map<std::string, unsigned int> terms;
};

class QueryCollection : public std::vector<QueryItem> {
private:
	std::ifstream stream; // Query file
	std::string line; // Currently processed line
	StopwordsCollection sw; // Stopwords

	void parseQueries();
	void processQuery(unsigned int id, std::string text);
	bool loadStopwords(std::string f);
	std::string gobbleText();
public:
	bool load(std::string fileName);
};

#endif /* SHARED_QUERYCOLLECTION_H_ */
