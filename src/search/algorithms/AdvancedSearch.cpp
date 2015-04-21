/*
 * AdvancedSearch.cpp
 */

#include "AdvancedSearch.h"

AdvancedSearch::AdvancedSearch() {}
AdvancedSearch::~AdvancedSearch() {}

/**
 * Searches using TF-IDF scoring method
 *
 * @param q The Query Item
 * @param compPerf Compute performance? (Precision & Recall)
 */
void AdvancedSearch::query(QueryItem q, bool compPerf) {
	double wQ = 0.0, precision = 0.0, recall = 0.0;
	std::map<unsigned int, double> results;
	std::map<double, unsigned int> results_sorted;

	for (auto const &term : q.terms) {
		if(c.terms.find(term.first) != c.terms.end()) {
			CollectionToken t = c.terms[term.first];
			double idf = std::log(1 + c.docs.size() / t.docs.size());
			wQ += std::pow(idf, 2);

			for(auto doc : t.docs) results[doc.id] += (1 + std::log(doc.freq)) * idf;
		}
	}

	wQ = std::sqrt(wQ);

	// Divide each score by (wQ * wD), and reverse the
	// map keys<->values to get it sorted by score
	for(std::map<unsigned int, double>::iterator it = results.begin(); it != results.end(); ++it) {
		it->second *= 1.0/ (wQ * c.docs[it->first].wD);
		results_sorted.insert({it->second, it->first});
	}

	// Display only the first 3% elements
	unsigned int count = results_sorted.size() * 0.03;
	cout << std::left  << std::setw(6)  << "Score" << " | " << std::right << std::setw(6)  << "Doc #" << " | ";
	cout << std::left  << std::setw(35) << "Authors" << " | " << std::left  << std::setw(30) << "Title" << endl;
	cout << "-------|--------|-------------------------------------|------------------------------------------------" << endl;

	std::map<double, unsigned int>::const_reverse_iterator it = results_sorted.rbegin();
	for(unsigned int i = 0; i != count; ++i) {
		cout << std::left  << std::setw(6)  << std::fixed << std::setprecision(3) << it->first << " | ";
		cout << std::right << std::setw(6)  << it->second << " | ";
		cout << std::left  << std::setw(35) << c.docs[it->second].authors << " | ";
		cout << std::left  << std::setw(40) << c.docs[it->second].title << endl;

		if(compPerf) {
			if(rc[q.id].find(it->second) != rc[q.id].end()) ++precision;
		}
		++it;
	}

	if(compPerf) {
		recall = precision / rc[q.id].size();
		precision /= count;

		cout << "Precision: " << precision << endl << "Recall: " << recall << endl;
	}
}

/**
 * uses the load() method of StopwordsCollection to read the stopwords
 */
bool AdvancedSearch::loadStopwords(std::string f) {
	return this->sw.load(f);
}

/**
 * Uses the load() method of Collection to read the inverted index
 *
 * @param fileName The file name of the index
 */
bool AdvancedSearch::loadCollection(std::string f) {
	return this->c.load(f);
}

/**
 * Uses the load() method of RelationsCollection to read the relations index
 *
 * @param fileName The file name of the index
 */
bool AdvancedSearch::loadRelations(std::string f) {
	return this->rc.load(f);
}
