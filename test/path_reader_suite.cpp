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

#include <trial/url/path_reader.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(path_reader_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_slash)
{
    const char input[] = "/";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_slash_slash)
{
    const char input[] = "//";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_unreserved)
{
    const char input[] = "/az09-._~";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "az09-._~");
    BOOST_REQUIRE_EQUAL(reader.segment(), "az09-._~");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_subdelims)
{
    const char input[] = "/!$&'()*+,;=";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "!$&'()*+,;=");
    BOOST_REQUIRE_EQUAL(reader.segment(), "!$&'()*+,;=");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_two_unreserved)
{
    const char input[] = "/alpha/bravo";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.segment(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), "bravo");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_at)
{
    const char input[] = "/@";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.segment(), "@");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_colon)
{
    const char input[] = "/:";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.segment(), ":");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_pct_encoded)
{
    const char input[] = "/%20";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "%20");
    BOOST_REQUIRE_EQUAL(reader.segment(), " ");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_pct_encoded_more)
{
    const char input[] = "/%20:%20";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_segment(), "%20:%20");
    BOOST_REQUIRE_EQUAL(reader.segment(), " : ");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_absolute_mix)
{
    const char input[] = "/a/0/./!/@/:/%20";
    url::path_reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.segment(), "a");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), "0");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), ".");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), "!");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), "@");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), ":");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.segment(), " ");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_SUITE_END()
