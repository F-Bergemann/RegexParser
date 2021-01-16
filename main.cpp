// Example how to use Boost Spirit to construct an abstract syntax tree (AST)
// for a simple arithmetic grammar and to evaluate expressions.
//
// The grammar accepts expressions like "1 + 2 * 3", constructs an AST and
// evaluates it correctly.

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <memory>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
namespace qi = boost::spirit::qi;

#include "RegexParser.h"

template <typename Parser, typename ... Args>
bool
Parse(
    const std::string& input,
	const Parser& p,
    Args&& ... args)
{
    auto begin = input.begin(), end = input.end();

    bool result = qi::parse(begin, end, p, std::forward<Args>(args) ...);

    if (!result || begin != end)
    {
        std::cout
		<< "Unparseable: '"
		<< input
        	<< "', failed at: '"
		<< std::string(begin, end)
		<< "'" 
        	<< std::endl;

        result = false;
    }
    return result;
}

void
TestRegexParser(
		std::string const & input)
{
	RegexParser::ASTNode* out_node;
	bool result = Parse(input, RegexParser::Grammar(), out_node);

	if (result) {
		std::cout << "print():" << input << std::endl;
		out_node->print(0);

		delete out_node;
	}
}
/******************************************************************************/

int
main(
		int argc,
		char* argv[])
{
    if (argc >= 2)
    {
    	TestRegexParser(argv[1]);
    }
    else
    {
    	// some initial trials
        TestRegexParser("a");
        TestRegexParser("aa");
        TestRegexParser("Hello, World!");
        TestRegexParser("FrankBergemann");

        // groups
        TestRegexParser("[a]");
        TestRegexParser("[ab]");
        TestRegexParser("[a-z]");
        TestRegexParser("[b-c]");
        TestRegexParser("[A-Z]");
        TestRegexParser("[a-zA-Z]");
        TestRegexParser("[abcABC]");

        // negative groups
        TestRegexParser("[^a]");
        TestRegexParser("[^ab]");
        TestRegexParser("[^a-z]");
        TestRegexParser("[^b-c]");
        TestRegexParser("[^A-Z]");
        TestRegexParser("[^a-zA-Z]");
        TestRegexParser("[^abcABC]");

        // '*'
        TestRegexParser("[abcABC]*");
        TestRegexParser("[^abcABC]*");

        // '+'
        TestRegexParser("[abcABC]+");
        TestRegexParser("[^abcABC]+");

        TestRegexParser("SomeStrange.*Patter[nN]");

        // currently crashing:
#if 0
        TestRegexParser("^SomeStrange.*Patter[nN]");
#endif
    }

    return 0;
}

/******************************************************************************/
