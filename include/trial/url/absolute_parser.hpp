#ifndef TRIAL_URL_ABSOLUTE_PARSER_HPP
#define TRIAL_URL_ABSOLUTE_PARSER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace url
{

// FIXME: RFC 3986 section 4.3 

template <typename CharT>
class basic_absolute_parser
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;
    typedef std::basic_string<value_type> string_type;

    basic_parser(const view_type&);

    const view_type& literal_scheme() const;
    const view_type& literal_authority() const;
    const view_type& literal_path() const;
    const view_type& literal_query() const;
};

typedef basic_absolute_parser<char> absolute_parser;

#endif // TRIAL_URL_ABSOLUTE_PARSER_HPP
