/*
 * BinaryQueryParser.cpp
 */

#include "BinaryQueryParser.h"

BinaryQueryParser::BinaryQueryParser(std::string q) {
	this->query = q;
	this->index = 0;

	// Split text in tokens
	boost::split(expr, query, boost::is_any_of("\t .-,;/"));
}

BinaryQueryParser::~BinaryQueryParser() {
	// TODO Auto-generated destructor stub
}

/*
 * Returns binary precedence
 *
 * @param std::string op The operator
 */
bool BinaryQueryParser::binaryPrecedence(std::string op){
	return binaryOperators[op] || 0;
}



/*Expression BinaryQueryParser::parse() {
	//return gobbleExpression();
}
*/
