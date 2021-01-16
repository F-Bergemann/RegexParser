/*
 * RegexParser.h
 *
 *  Created on: Dec 28, 2020
 *      Author: frank
 */

#ifndef REGEXPARSER_H_
#define REGEXPARSER_H_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace RegexParser {

class ASTNode
{
public:
	ASTNode(std::string val)
	{ /* void */ };

	ASTNode (char const ch)
	{ /* void */ };

    void print(int indent)
    { /* void */ }

    virtual ~ASTNode()
    { /* void */ }
};

using ASTNodePtr = ASTNode*;

class Grammar : public qi::grammar<std::string::const_iterator, ASTNode*>
{
public:
    using Iterator = std::string::const_iterator;

    Grammar();

    qi::rule<Iterator, ASTNode*> 
    	tok_RE, tok_union, tok_simple_RE,
		tok_concatenation, tok_basic_RE,
		tok_star, tok_plus, tok_elementary_RE,
		tok_group, tok_any, tok_eos ,tok_char, tok_set,
		tok_positive_set, tok_negative_set,
		tok_set_items, tok_set_item,
		tok_range;
};

}

#endif /* REGEXPARSER_H_ */
