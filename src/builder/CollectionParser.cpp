/*
 * CollectionParser.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: alfo
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CollectionParser.h"

CollectionParser::CollectionParser(std::string f) {
	stream.open(f.c_str());

	if(!stream) {
		std::cerr << "Error opening collection file." << std::endl << "Exiting." << std::endl;
		exit(-1);
	}

}

CollectionParser::~CollectionParser() {
	stream.close();
}

/**
 * Reads the file up to the ".I" prefix to gather the ID.
 */
unsigned int CollectionParser::gobbleId() {
	std::string prefix(".I");

	do {
		if (!line.compare(0, prefix.size(), prefix))
			return (unsigned int) std::atoi(line.substr(prefix.size()).c_str());
	} while(std::getline(stream, line));

	return -1;
}

/**
 * Reads the file up to the ".T" prefix to gather the Title.
 */
std::string CollectionParser::gobbleTitle() {
	std::string prefix(".T");
	std::string prefixDot(".");
	std::string title;

	do {
		if (!line.compare(0, prefix.size(), prefix)) {
			std::getline(stream, line);
			while(!std::equal(prefixDot.begin(), prefixDot.end(), line.begin())) {
				title.append(line + " ");
				std::getline(stream, line);
			}
			break;
		}
	} while(std::getline(stream, line));

	return title;
}

/**
 * Reads the file up to the ".A" prefix to gather the Authors.
 */
std::string CollectionParser::gobbleAuthors() {
	std::string prefix(".A");

	do {
		if (!line.compare(0, prefix.size(), prefix)) {
			std::getline(stream, line);
			return line;
		}
	} while(std::getline(stream, line));

	return std::string("");
}

/**
 * Reads the file up to the ".W" prefix to gather the Text.
 */
std::string CollectionParser::gobbleText() {
	std::string prefix(".W");
	std::string prefixDot(".");
	std::string text;

	do {
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

		if (!line.compare(0, prefix.size(), prefix)) {
			std::getline(stream, line);
			line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

			while(!stream.eof() && !std::equal(prefixDot.begin(), prefixDot.end(), line.begin())) {
				text.append(line + " ");

				std::getline(stream, line);
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
			}
			break;
		}
	} while(std::getline(stream, line));

	return text;
}

/**
 * Reads the entire collection file and start its processing
 */
void CollectionParser::parseCollection() {

	while(!stream.eof())
	{
		unsigned int id = this->gobbleId();
		std::string title = this->gobbleTitle();
		std::string authors = this->gobbleAuthors();
		std::string text = this->gobbleText();

		processDocument(id, authors, title, text);
	}
}

/**
 * Processes one Document. Steps:
 * 1. Lowercase
 * 2. Split into tokens using these separators: "\t .-,;/"
 * 3. Remove empty words
 * 4. Remove stopwords
 * 5. Stem each token
 * 6. Sort
 * 7. Compute occurrences of each stem
 * 8. Add stems to inverted index
 * 9. Compute wD
 */
void CollectionParser::processDocument(unsigned int id, string authors, string title, string text) {

	std::list<string> tokens;
	std::map<string, unsigned int> stems;
	double wD = 0.0;

	// Transform text to lowercase
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);

	// Split text in tokens
	boost::split(tokens, text, boost::is_any_of("\t .-,;/"));

	// Remove when length == 0
	tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](string w) { return !w.length(); }), tokens.end());

	// Remove stopwords
	tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [this](string w) { return (this->sw.find(w) != this->sw.end()); }), tokens.end());

	// Stem each word
	std::for_each(tokens.begin(), tokens.end(), [](string &w){ Porter2Stemmer::stem(w); });

	// Sort
	tokens.sort();

	// Compute occurrences
	for (list<string>::iterator it = tokens.begin(); it!=tokens.end(); ++it) {
		if(stems.find(*it) != stems.end()) ++stems[*it];
		else stems[*it] = 1;
	}

	// Add stems to inverted index & compute wD factors
	for(auto const &i : stems) {
		// If term already present in index
		if(c.terms.find(i.first) != c.terms.end()) c.terms[i.first].freq += i.second;
		else c.terms[i.first].freq = i.second;

		// Add document to the list of documents containing this stem
		c.terms[i.first].docs.push_back({ id, i.second });

		// wD = (1 + log(#occ))^2
		wD += std::pow(1 + std::log(i.second), 2);
	}

	wD = std::sqrt(wD);

	// Populate document informations
	c.docs[id] = { title, authors, wD };

	/*for(auto const &i : c.terms) {
		cout << i.first << "\t\t" << i.second.freq  << "\t\t" << wD << endl;
	}*/
}

bool CollectionParser::loadStopwords(std::string f) {
	return this->sw.load(f);
}

Collection CollectionParser::getCollection() {
	return this->c;
}
