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

#include <trial/url/parser.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(parser_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "");
    BOOST_REQUIRE_EQUAL(parser.authority(), "");
    BOOST_REQUIRE_EQUAL(parser.path(), "");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

BOOST_AUTO_TEST_CASE(test_scheme)
{
    const char input[] = "scheme://";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "");
    BOOST_REQUIRE_EQUAL(parser.path(), "");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

BOOST_AUTO_TEST_CASE(test_host)
{
    const char input[] = "scheme://1.2.3.4";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.path(), "");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

BOOST_AUTO_TEST_CASE(test_host_port)
{
    const char input[] = "scheme://1.2.3.4:80";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "1.2.3.4:80");
    BOOST_REQUIRE_EQUAL(parser.path(), "");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

BOOST_AUTO_TEST_CASE(test_host_port_slash)
{
    const char input[] = "scheme://1.2.3.4:80/";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "1.2.3.4:80");
    BOOST_REQUIRE_EQUAL(parser.path(), "/");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

//-----------------------------------------------------------------------------
// Path
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_path_plain)
{
    const char input[] = "scheme://example.com/path";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "example.com");
    BOOST_REQUIRE_EQUAL(parser.path(), "/path");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

//-----------------------------------------------------------------------------
// Query
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_query_plain)
{
    const char input[] = "scheme://example.com/path?query";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "example.com");
    BOOST_REQUIRE_EQUAL(parser.path(), "/path");
    BOOST_REQUIRE_EQUAL(parser.query(), "query");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "");
}

//-----------------------------------------------------------------------------
// Fragment
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_fragment_plain)
{
    const char input[] = "scheme://example.com/path#fragment";
    url::parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.scheme(), "scheme");
    BOOST_REQUIRE_EQUAL(parser.authority(), "example.com");
    BOOST_REQUIRE_EQUAL(parser.path(), "/path");
    BOOST_REQUIRE_EQUAL(parser.query(), "");
    BOOST_REQUIRE_EQUAL(parser.fragment(), "fragment");
}

BOOST_AUTO_TEST_SUITE_END()
