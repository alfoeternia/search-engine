/*
 * QueryCollection.cpp
 */

#include "QueryCollection.h"

bool QueryCollection::load(std::string fileName) {
	stream.open(fileName.c_str());

	if(!stream) {
		std::cerr << "Error opening queries file." << std::endl << "Exiting." << std::endl;
		return false;
	}

	this->parseQueries();
	stream.close();

	return true;
}

std::string QueryCollection::gobbleText() {
	std::string prefix(".W");
	std::string prefixDot(".");
	std::string text = "";

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
 * Reads the entire queries collection file and start its processing
 */
void QueryCollection::parseQueries() {
	// NB: Id is not gathered from the queries file but incremented
	unsigned int currentId = 0;

	while(!stream.eof())
	{
		unsigned int id = ++currentId;
		std::string text = this->gobbleText();

		//std::cout << "Query " << id << " -> " << text << std::endl;

		processQuery(id, text);

	}
}

/**
 * Processes one Query. Steps:
 * 1. Lowercase
 * 2. Split into tokens using these separators: "\t .-,;/"
 * 3. Remove empty words
 * 4. Remove stopwords
 * 5. Stem each token
 * 6. Sort terms
 * 7. Compute occurrences of each stem
 * 8. Add query to query collection
 */
void QueryCollection::processQuery(unsigned int id, std::string text) {

	std::list<string> tokens;
	std::map<std::string, unsigned int> terms;

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
		if(terms.find(*it) != terms.end()) ++terms[*it];
		else terms[*it] = 1;
	}

	// Push query to the list
	//this->c.queries.push_back(q);
	this->push_back({id, text, terms});
}


/**
 * uses the load() method of StopwordsCollection to read the stopwords
 */
bool QueryCollection::loadStopwords(std::string f) {
	return this->sw.load(f);
}
