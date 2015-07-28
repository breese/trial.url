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

#include <trial/url/reader/query_form.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(reader_query_form_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_single_pair)
{
    const char input[] = "alpha=hydrogen";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.literal_value(), "hydrogen");
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "hydrogen");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_single_space)
{
    const char input[] = "alpha=hydrogen+helium";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.literal_value(), "hydrogen+helium");
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "hydrogen helium");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_single_equal)
{
    const char input[] = "alpha=hydrogen%3Dhelium";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.literal_value(), "hydrogen%3Dhelium");
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "hydrogen=helium");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_list_two)
{
    const char input[] = "alpha=hydrogen&bravo=helium";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "hydrogen");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.key(), "bravo");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "helium");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_list_three)
{
    const char input[] = "alpha=hydrogen&bravo=helium&charlie=lithium";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "hydrogen");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.key(), "bravo");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "helium");
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.key(), "charlie");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "lithium");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_percent)
{
    const char input[] = "alpha=%20";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.literal_key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.literal_value(), "%20");
    BOOST_REQUIRE_EQUAL(reader.key(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), " ");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(fail_ampersand)
{
    const char input[] = "&";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(fail_no_value)
{
    const char input[] = "alpha=";
    url::reader::query_form reader(input);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_SUITE_END()
