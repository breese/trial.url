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

#include <trial/url/authority_parser.hpp>

namespace url = trial::url;

BOOST_AUTO_TEST_SUITE(authority_parser_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_host)
{
    const char input[] = "1.2.3.4";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_host_port)
{
    const char input[] = "1.2.3.4:80";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "80");
}

BOOST_AUTO_TEST_CASE(test_userinfo_host_port)
{
    const char input[] = "user@1.2.3.4:80";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "user");
    BOOST_REQUIRE_EQUAL(parser.host(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "80");
}

BOOST_AUTO_TEST_CASE(test_host_regname)
{
    const char input[] = "example.com";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "example.com");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

//-----------------------------------------------------------------------------
// IPv4 address
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_ipv4_increasing)
{
    const char input[] = "0.1.2.3";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "0.1.2.3");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv4_zeroes)
{
    const char input[] = "0.0.0.0";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "0.0.0.0");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv4_ones)
{
    const char input[] = "1.10.100.0";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1.10.100.0");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv4_twos)
{
    const char input[] = "2.20.200.0";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "2.20.200.0");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv4_two_halfs)
{
    const char input[] = "2.25.250.255";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "2.25.250.255");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv4_large_regname)
{
    const char input[] = "256.0.0.0";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "256.0.0.0"); // Matches regname
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

//-----------------------------------------------------------------------------
// IPv6 address
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_ipv6_line_1_v6)
{
    const char input[] = "[AAAA:BBBB:CCCC:DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "AAAA:BBBB:CCCC:DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_1_v4)
{
    const char input[] = "[AAAA:BBBB:CCCC:DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "AAAA:BBBB:CCCC:DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_2_v6)
{
    const char input[] = "[::BBBB:CCCC:DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "::BBBB:CCCC:DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_2_v4)
{
    const char input[] = "[::BBBB:CCCC:DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "::BBBB:CCCC:DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_3a_v6)
{
    const char input[] = "[::CCCC:DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "::CCCC:DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_3a_v4)
{
    const char input[] = "[::CCCC:DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "::CCCC:DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_3b_v6)
{
    const char input[] = "[1111::CCCC:DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::CCCC:DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_3b_v4)
{
    const char input[] = "[1111::CCCC:DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::CCCC:DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_4a_v6)
{
    const char input[] = "[1111::DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_4a_v4)
{
    const char input[] = "[1111::DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_4b_v6)
{
    const char input[] = "[1111:2222::DDDD:EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::DDDD:EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_4b_v4)
{
    const char input[] = "[1111:2222::DDDD:EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::DDDD:EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5a_v6)
{
    const char input[] = "[1111::EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5a_v4)
{
    const char input[] = "[1111::EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5b_v6)
{
    const char input[] = "[1111:2222::EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5b_v4)
{
    const char input[] = "[1111:2222::EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5c_v6)
{
    const char input[] = "[1111:2222:3333::EEEE:FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::EEEE:FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_5c_v4)
{
    const char input[] = "[1111:2222:3333::EEEE:FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::EEEE:FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6a_v6)
{
    const char input[] = "[1111::FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6a_v4)
{
    const char input[] = "[1111::FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6b_v6)
{
    const char input[] = "[1111:2222::FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6b_v4)
{
    const char input[] = "[1111:2222::FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6c_v6)
{
    const char input[] = "[1111:2222:3333::FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6c_v4)
{
    const char input[] = "[1111:2222:3333::FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6d_v6)
{
    const char input[] = "[1111:2222:3333:4444::FFFF:1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::FFFF:1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_6d_v4)
{
    const char input[] = "[1111:2222:3333:4444::FFFF:1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::FFFF:1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7a_v6)
{
    const char input[] = "[1111::1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7a_v4)
{
    const char input[] = "[1111::1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7b_v6)
{
    const char input[] = "[1111:2222::1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7b_v4)
{
    const char input[] = "[1111:2222::1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7c_v6)
{
    const char input[] = "[1111:2222:3333::1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7c_v4)
{
    const char input[] = "[1111:2222:3333::1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7d_v6)
{
    const char input[] = "[1111:2222:3333:4444::1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7d_v4)
{
    const char input[] = "[1111:2222:3333:4444::1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7e_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555::1234:5678]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555::1234:5678");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_7e_v4)
{
    const char input[] = "[1111:2222:3333:4444:5555::1.2.3.4]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555::1.2.3.4");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8a_v6)
{
    const char input[] = "[1111::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8b_v6)
{
    const char input[] = "[1111:2222::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8c_v6)
{
    const char input[] = "[1111:2222:3333::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8d_v6)
{
    const char input[] = "[1111:2222:3333:4444::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8e_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_8f_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555:6666::1234]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555:6666::1234");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9a_v6)
{
    const char input[] = "[1111::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9b_v6)
{
    const char input[] = "[1111:2222::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9c_v6)
{
    const char input[] = "[1111:2222:3333::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9d_v6)
{
    const char input[] = "[1111:2222:3333:4444::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9e_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9f_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555:6666::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555:6666::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_CASE(test_ipv6_line_9g_v6)
{
    const char input[] = "[1111:2222:3333:4444:5555:6666:7777::]";
    url::authority_parser parser(input);
    BOOST_REQUIRE_EQUAL(parser.userinfo(), "");
    BOOST_REQUIRE_EQUAL(parser.host(), "1111:2222:3333:4444:5555:6666:7777::");
    BOOST_REQUIRE_EQUAL(parser.port(), "");
}

BOOST_AUTO_TEST_SUITE_END()
