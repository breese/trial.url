
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

#include <trial/url/reader.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(reader_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.category(), url::token::category::error);
    BOOST_REQUIRE_EQUAL(reader.code(), url::token::code::end);
    BOOST_REQUIRE_EQUAL(reader.literal(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_scheme)
{
    const char input[] = "scheme:";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.category(), url::token::category::scheme);
    BOOST_REQUIRE_EQUAL(reader.code(), url::token::code::scheme);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_host_empty)
{
    const char input[] = "scheme://";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_host)
{
    const char input[] = "scheme://1.2.3.4";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_ipv4);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_host_port)
{
    const char input[] = "scheme://1.2.3.4:80";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_ipv4);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_port);
    BOOST_REQUIRE_EQUAL(reader.literal(), "80");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_host_port_slash)
{
    const char input[] = "scheme://1.2.3.4:80/";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_ipv4);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_port);
    BOOST_REQUIRE_EQUAL(reader.literal(), "80");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

//-----------------------------------------------------------------------------
// Path
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_path_plain)
{
    const char input[] = "scheme://example.com/path";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_name);
    BOOST_REQUIRE_EQUAL(reader.literal(), "example.com");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.category(), url::token::category::path);
    BOOST_REQUIRE_EQUAL(reader.code(), url::token::code::path_segment);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "path");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

//-----------------------------------------------------------------------------
// Query
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_query_plain)
{
    const char input[] = "scheme://example.com/path?query";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_name);
    BOOST_REQUIRE_EQUAL(reader.literal(), "example.com");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "path");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.category(), url::token::category::query);
    BOOST_REQUIRE_EQUAL(reader.code(), url::token::code::query);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::query);
    BOOST_REQUIRE_EQUAL(reader.literal(), "query");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

//-----------------------------------------------------------------------------
// Fragment
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_fragment_plain)
{
    const char input[] = "scheme://example.com/path#fragment";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_name);
    BOOST_REQUIRE_EQUAL(reader.literal(), "example.com");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "path");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.category(), url::token::category::fragment);
    BOOST_REQUIRE_EQUAL(reader.code(), url::token::code::fragment);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::fragment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "fragment");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_query_fragment_plain)
{
    const char input[] = "scheme://example.com/path?query#fragment";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_name);
    BOOST_REQUIRE_EQUAL(reader.literal(), "example.com");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "path");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::query);
    BOOST_REQUIRE_EQUAL(reader.literal(), "query");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::fragment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "fragment");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_fragment_question)
{
    const char input[] = "scheme://example.com/path#fragment?query";
    url::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::scheme);
    BOOST_REQUIRE_EQUAL(reader.literal(), "scheme");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::authority_host_name);
    BOOST_REQUIRE_EQUAL(reader.literal(), "example.com");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::path_segment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "path");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.subcode(), url::token::subcode::fragment);
    BOOST_REQUIRE_EQUAL(reader.literal(), "fragment?query");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_SUITE_END()
