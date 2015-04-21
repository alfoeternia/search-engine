/*
 * AdvancedSearch.h
 */

#ifndef SRC_ADVANCEDSEARCH_H_
#define SRC_ADVANCEDSEARCH_H_

#include <parallel/algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
using std::string;
#include <iomanip>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <list>
#include <map>
#include <set>
#include <vector>
using std::vector;

#include "../../shared/Collection.h"
#include "../../shared/QueryCollection.h"
#include "../../shared/RelationsCollection.h"
#include "../../shared/StopwordsCollection.h"
#include "../../lib/porter2_stemmer.h"

class AdvancedSearch {

private:
	StopwordsCollection sw; // Stopwords
	Collection c;
	RelationsCollection rc;

public:
	AdvancedSearch();
	virtual ~AdvancedSearch();

	void query(QueryItem q, bool compPerf = false);
	bool loadCollection(std::string f);
	bool loadRelations(std::string f);
	bool loadStopwords(std::string f);
};

#endif /* SRC_ADVANCEDSEARCH_H_ */
