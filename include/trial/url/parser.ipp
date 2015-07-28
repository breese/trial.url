#ifndef TRIAL_URL_PARSER_IPP
#define TRIAL_URL_PARSER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/url/reader.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
basic_parser<CharT>::basic_parser(const view_type& input)
{
    parse(input);
}

//-----------------------------------------------------------------------------
// Accessors
//-----------------------------------------------------------------------------

template <typename CharT>
const typename basic_parser<CharT>::view_type&
basic_parser<CharT>::literal_scheme() const
{
    return current_scheme;
}

template <typename CharT>
const typename basic_parser<CharT>::view_type&
basic_parser<CharT>::literal_authority() const
{
    return current_authority;
}

template <typename CharT>
const typename basic_parser<CharT>::view_type&
basic_parser<CharT>::literal_path() const
{
    return current_path;
}

template <typename CharT>
const typename basic_parser<CharT>::view_type&
basic_parser<CharT>::literal_query() const
{
    return current_query;
}

template <typename CharT>
const typename basic_parser<CharT>::view_type&
basic_parser<CharT>::literal_fragment() const
{
    return current_fragment;
}

template <typename CharT>
typename basic_parser<CharT>::string_type
basic_parser<CharT>::scheme() const
{
    return string_type(current_scheme.begin(), current_scheme.end());
}

template <typename CharT>
typename basic_parser<CharT>::string_type
basic_parser<CharT>::authority() const
{
    return string_type(current_authority.begin(), current_authority.end());
}

template <typename CharT>
typename basic_parser<CharT>::string_type
basic_parser<CharT>::path() const
{
    return string_type(current_path.begin(), current_path.end());
}

template <typename CharT>
typename basic_parser<CharT>::string_type
basic_parser<CharT>::query() const
{
    return string_type(current_query.begin(), current_query.end());
}

template <typename CharT>
typename basic_parser<CharT>::string_type
basic_parser<CharT>::fragment() const
{
    return string_type(current_fragment.begin(), current_fragment.end());
}

//-----------------------------------------------------------------------------
// Parser
//-----------------------------------------------------------------------------

template <typename CharT>
void basic_parser<CharT>::parse(const view_type& input)
{
    url::basic_reader<CharT> reader(input);

    typename view_type::const_iterator authority_begin = input.end();
    typename view_type::const_iterator authority_end = input.end();
    typename view_type::const_iterator path_begin = input.end();
    typename view_type::const_iterator path_end = input.end();
    do
    {
        switch (reader.code())
        {
        case token::code::end:
        case token::code::error:
            break;

        case token::code::scheme:
            current_scheme = reader.literal();
            break;

        case token::code::authority_userinfo:
            authority_begin = reader.literal().begin();
            authority_end = reader.literal().end();
            break;

        case token::code::authority_host:
            if (authority_begin == input.end())
                authority_begin = reader.literal().begin();
            authority_end = reader.literal().end();
            break;

        case token::code::authority_port:
            authority_end = reader.literal().end();
            break;

        case token::code::path_segment:
            if (path_begin == input.end())
                path_begin = reader.literal().begin() - 1; // Include initial /
            path_end = reader.literal().end();
            break;

        case token::code::query:
            current_query = reader.literal();
            break;

        case token::code::fragment:
            current_fragment = reader.literal();
            break;
        }
    } while (reader.next());

    current_authority = view_type(authority_begin, std::distance(authority_begin, authority_end));
    current_path = view_type(path_begin, std::distance(path_begin, path_end));
}

} // namespace url
} // namespace trial

#endif // TRIAL_URL_PARSER_IPP
