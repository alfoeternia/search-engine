/*
 * CollectionParser.h
 */

#ifndef COLLECTIONPARSER_H_
#define COLLECTIONPARSER_H_

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <cstdlib>
#include <cstring>
using std::string;
#include <functional>
#include <fstream>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <list>
using std::list;
#include <map>
#include <set>
#include <vector>
using std::vector;

#include "../shared/Collection.h"
#include "../shared/StopwordsCollection.h"
#include "../lib/porter2_stemmer.h"

class CollectionParser {

private:
	std::ifstream stream; // Stream to the collection file
	std::string line; // Currently processed line
	StopwordsCollection sw; // Stopwords
	Collection c;

public:
	CollectionParser(std::string f);
	virtual ~CollectionParser();

	void parseCollection();
	void processDocument(unsigned int id, std::string authors, std::string title, std::string text);
	bool loadStopwords(std::string f);
	Collection getCollection();

	unsigned int gobbleId();
	std::string gobbleAuthors();
	std::string gobbleTitle();
	std::string gobbleText();
};

#endif /* COLLECTIONPARSER_H_ */
