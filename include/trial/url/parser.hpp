#ifndef TRIAL_URL_PARSER_HPP
#define TRIAL_URL_PARSER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/utility/string_ref.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
class basic_parser
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
    const view_type& literal_fragment() const;

    string_type scheme() const;
    string_type authority() const;
    string_type path() const;
    string_type query() const;
    string_type fragment() const;

private:
    void parse(view_type);
    std::size_t parse_scheme(const view_type&);
    std::size_t parse_hier_part(const view_type&);
    std::size_t parse_authority(const view_type&);
    std::size_t parse_path(const view_type&);
    std::size_t parse_query(const view_type&);
    std::size_t parse_fragment(const view_type&);

private:
    view_type current_scheme;
    view_type current_authority;
    view_type current_path;
    view_type current_query;
    view_type current_fragment;
};

typedef basic_parser<char> parser;

} // namespace url
} // namespace trial

#include <trial/url/parser.ipp>

#endif // TRIAL_URL_PARSER_HPP
