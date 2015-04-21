/*
 * Collection.h
 */

#ifndef SHARED_COLLECTION_H_
#define SHARED_COLLECTION_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>


struct CollectionDocTermFrq {
	unsigned int id; // Document ID
	unsigned int freq; // Frequency of the term in this document

	template<class Archive> void serialize(Archive & a, const unsigned int v) { a & id & freq; }
};

struct CollectionToken {
	unsigned int freq;
	std::vector<CollectionDocTermFrq> docs;

	template<class Archive> void serialize(Archive & a, const unsigned int v) { a & freq & docs; }
};

struct CollectionDocInfo {
	std::string title;
	std::string authors;
	double wD;

	template<class Archive> void serialize(Archive & a, const unsigned int v) { a & title & authors & wD; }
};

class Collection {
private:
    friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & a, const unsigned int v) { a & terms & docs; }

public:
	Collection();
	virtual ~Collection();

	std::map<std::string, CollectionToken> terms;
	std::map<unsigned int, CollectionDocInfo> docs;

	bool save(std::string fileName);
	bool load(std::string fileName);

};

#endif /* SHARED_COLLECTION_H_ */
