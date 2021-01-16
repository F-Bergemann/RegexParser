/*
 * RegexParser.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: frank
 */

#include <boost/spirit/include/qi_char_class.hpp>

#include "RegexParser.h"

#define TEST 1

namespace RegexParser {

Grammar::Grammar()
: Grammar::base_type(tok_RE)
{
	// BNF grammar from here: https://www2.cs.sfu.ca/~cameron/Teaching/384/99-3/regexp-plg.html

	tok_RE =
			tok_simple_RE | tok_union;

	tok_union =
			tok_RE  >> '|' >> tok_simple_RE;

#if 1
	tok_simple_RE =
			tok_basic_RE >> *tok_basic_RE;
#else // TODO: does not parse "aa"
	tok_simple_RE =
			tok_basic_RE | tok_concatenation; // TODO: coredump if exchanging the sequence or '|' arguments (?!)

	tok_concatenation =
			tok_simple_RE >> tok_basic_RE;
#endif
	tok_basic_RE =
			tok_star | tok_plus | tok_elementary_RE;

	tok_star =
			tok_elementary_RE >> '*';

	tok_plus =
			tok_elementary_RE >> '+';

	tok_elementary_RE =
			tok_group | tok_any | tok_eos | tok_char | tok_set;

	tok_group  =
			'(' >> tok_RE >> ')';

	tok_any =
			qi::char_('.') [ qi::_val = phx::new_<ASTNode> ('.') ];

	tok_eos =
			qi::char_('$') [ qi::_val = phx::new_<ASTNode> ('$') ];

	tok_char =
			 boost::spirit::ascii::alnum [ qi::_val = phx::new_<ASTNode> ('?') ]; // TODO BNF: <char> 	::= 	any non metacharacter | "\" metacharacter

	tok_set =
			tok_positive_set | tok_negative_set;

	tok_positive_set =
			'[' >> tok_set_items >> ']';

	tok_negative_set =
			"[^" >> tok_set_items >> ']';

	tok_set_items =
			tok_set_item >> *tok_set_item;

	tok_set_item =
			tok_range | tok_char;

	tok_range =
			tok_char >> '-' >> tok_char ;

}

} // namespace RegexParser
