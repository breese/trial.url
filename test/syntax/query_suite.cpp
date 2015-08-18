///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <trial/url/syntax/query.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(syntax_query_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::string input("");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), 0);
}

BOOST_AUTO_TEST_CASE(test_key_value)
{
    std::string input("key=value");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), input.size());
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::decode(input), input);
}

BOOST_AUTO_TEST_CASE(test_slash)
{
    std::string input("a/b");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), input.size());
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::decode(input), input);
}

BOOST_AUTO_TEST_CASE(test_question_mark)
{
    std::string input("a?b");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), input.size());
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::decode(input), input);
}

BOOST_AUTO_TEST_CASE(test_until_fragment)
{
    std::string input("key=value#fragment");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), 9);
}

BOOST_AUTO_TEST_CASE(test_pct_encoded)
{
    std::string input("one%20two");
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::match(input), input.size());
    BOOST_REQUIRE_EQUAL(url::syntax::query<char>::decode(input), "one two");
}

BOOST_AUTO_TEST_SUITE_END()
