/*
 * search.cpp
 */

#include <parallel/algorithm>
#include <parallel/settings.h>
#include <iostream>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>

#include "../shared/QueryCollection.h"
#include "algorithms/AdvancedSearch.h"
#include "algorithms/BinarySearch.h"


int main(int argc, char const *argv[])
{
	__gnu_parallel::_Settings s;
	s.algorithm_strategy = __gnu_parallel::force_parallel;
	__gnu_parallel::_Settings::set(s);

	try {

		// Parse command-line arguments
		TCLAP::CmdLine cmd("Search engine", ' ', "1.0");
		TCLAP::SwitchArg binarySwitch("b", "binary", "Performs a binary search", cmd, false);
		TCLAP::ValueArg<std::string> indexArg("i", "index", "Specify index file (default: ./docs/index.oarchive)", false, "./docs/index.oarchive", "string");
		TCLAP::ValueArg<std::string> stopwordsArg("w", "stopwords", "Specifies a custom stopwords file (default: ./docs/stopwords.txt)", false, "./docs/stopwords.txt", "string");
		TCLAP::ValueArg<std::string> bulkArg("B", "bulk", "Bulk process queries file (default: ./docs/cran.qry)", false, "./docs/cran.qry", "string");
		TCLAP::ValueArg<std::string> perfArg("p", "compute-performance", "Compute performance using query-relations file (default: ./docs/cranqrel)", false, "./docs/cranqrel", "string");
		TCLAP::UnlabeledMultiArg<std::string>  queriesArg("Queries", "Queries", false, "", "string");

		cmd.add(indexArg);
		cmd.add(stopwordsArg);
		cmd.add(bulkArg);
		cmd.add(perfArg);
		cmd.add(queriesArg);
		cmd.parse(argc, argv);

		/// BINARY SEARCH
		if(binarySwitch.isSet()) {
			//BinarySearch *search = new BinarySearch();
			//search->loadCollection(indexArg.getValue());

			std::cerr << "Binary search not implemented yet." << std::endl;

			//delete search;
		}

		/// TF-IDF SEARCH
		else {
			AdvancedSearch *search = new AdvancedSearch();
			search->loadCollection(indexArg.getValue());
			search->loadStopwords(stopwordsArg.getValue());
			if(perfArg.isSet()) search->loadRelations(perfArg.getValue());

			// Process queries file
			if(bulkArg.isSet()) {
				unsigned int id = 0;
				QueryCollection qc;
				qc.load(bulkArg.getValue());

				for(auto const &q : qc) {
					std::cout << "Processing query " << ++id << ": " << q.text << std::endl;
					search->query(q, perfArg.isSet());
				}

			}
			// Process queries given as parameter
			else {
				for(auto const &q : queriesArg.getValue()) {
					std::cout << "Query: " << q << std::endl;
					std::cerr << "Not implemented yet: please use Bulk mode (-B) with query file." << std::endl;
				}
			}

			delete search;
		}

	} catch (TCLAP::ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}


