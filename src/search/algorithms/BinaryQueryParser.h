/*
 * BinaryQueryParser.h
 */

#ifndef SRC_BINARYQUERYPARSER_H_
#define SRC_BINARYQUERYPARSER_H_

#include <boost/algorithm/string.hpp>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <map>
#include <string>
using std::string;
#include <vector>

class BinaryQueryParser {
private:
	std::string query;
	std::list<std::string> expr;
	unsigned int index;
	std::map<std::string, unsigned int> binaryOperators {{"OR", 1}, {"AND", 2}};

public:
	BinaryQueryParser(std::string q);
	virtual ~BinaryQueryParser();

	bool binaryPrecedence(std::string op);
	bool isIdentifier(std::string s);
	/*Expression createBinaryExpression(std::string op, std::string left, std::string right);
	Expression parse();

	std::string gobbleBinaryOp();
	Expression gobbleExpression();
	std::string gobbleToken();
	std::string gobbleIdentifier();
	std::string gobbleGroup();*/

};

class Expression {
public:
	std::string op;
};

class UnaryExpression : public Expression {
	std::string arg;
};

class BinaryExpression : public Expression {
	std::string left;
	std::string right;
};

#endif /* SRC_BINARYQUERYPARSER_H_ */
