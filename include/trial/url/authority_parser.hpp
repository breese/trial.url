#ifndef TRIAL_URL_AUTHORITY_PARSER_HPP
#define TRIAL_URL_AUTHORITY_PARSER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/utility/string_ref.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
class basic_authority_parser
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    basic_authority_parser(const view_type&);

    const view_type& authority() const;
    const view_type& userinfo() const;
    const view_type& host() const;
    const view_type& port() const;

private:
    std::size_t parse(const view_type&);
    std::size_t parse_host(const view_type&);

private:
    view_type current_authority;
    view_type current_userinfo;
    view_type current_host;
    view_type current_port;
};

typedef basic_authority_parser<char> authority_parser;

} // namespace url
} // namespace trial

#include <trial/url/authority_parser.ipp>

#endif // TRIAL_URL_AUTHORITY_PARSER_HPP
