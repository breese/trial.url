///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <trial/url/syntax/port.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(syntax_port_suite)

BOOST_AUTO_TEST_CASE(test_zero)
{
    std::string input("0");
    BOOST_REQUIRE_EQUAL(url::syntax::port<char>::match(input), 1);
    BOOST_REQUIRE_EQUAL(url::syntax::port<char>::decode<short>(input), 0);
}

BOOST_AUTO_TEST_CASE(test_8080)
{
    std::string input("8080");
    BOOST_REQUIRE_EQUAL(url::syntax::port<char>::match(input), 4);
    BOOST_REQUIRE_EQUAL(url::syntax::port<char>::decode<short>(input), 8080);
}

BOOST_AUTO_TEST_SUITE_END()
