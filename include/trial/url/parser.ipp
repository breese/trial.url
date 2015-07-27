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

#include <trial/url/syntax/character.hpp>
#include <trial/url/syntax/scheme.hpp>
#include <trial/url/authority_reader.hpp>
#include <trial/url/path_reader.hpp>

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
void basic_parser<CharT>::parse(view_type input)
{
    // RFC 3986 Section 3
    //
    // URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
    //
    // RFC 7230 Section 5.3
    //
    // request-target = origin-form
    //                / absolute-form
    //                / authority-form
    //                / asterisk-form

    if (input.empty())
        return;

    std::size_t processed = 0;
    if (input.front() != syntax::character<value_type>::alpha_slash)
    {
        processed = parse_scheme(input);
        input.remove_prefix(processed);

        if (input.empty() || (input.front() != syntax::character<value_type>::alpha_colon))
            return; // FIXME: Report error
        input.remove_prefix(1);
    }

    processed = parse_hier_part(input);
    if (processed == 0)
        return;
    input.remove_prefix(processed);
    if (input.empty())
        return;

    if (input.front() == syntax::character<value_type>::alpha_question_mark)
    {
        input.remove_prefix(1);
        processed = parse_query(input);
        if (processed == 0)
            return;
        if (input.empty())
            return;
    }
    if (input.front() == syntax::character<value_type>::alpha_number_sign)
    {
        input.remove_prefix(1);
        processed = parse_fragment(input);
        if (processed == 0)
            return;
        if (input.empty())
            return;
    }
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_scheme(const view_type& input)
{
    std::size_t processed = syntax::scheme<value_type>::match(input);
    if (processed > 0)
        current_scheme = input.substr(0, processed);
    return processed;
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_hier_part(const view_type& input)
{
    // RFC 3986 Section 3
    //
    // hier-part = "//" authority path-abempty
    //           / path-absolute
    //           / path-rootless
    //           / path-empty

    std::size_t current = 0;
    std::size_t processed = 0;

    if (input[current] == syntax::character<value_type>::alpha_slash)
    {
        ++current;
        if (input[current] == syntax::character<value_type>::alpha_slash)
        {
            ++current;
            processed = parse_authority(input.substr(current));
            if (processed == 0)
                return 0;
            current_authority = input.substr(current, processed);
            current += processed;
        }
    }
    processed = parse_path(input.substr(current));
    if (processed == 0)
        return current;
    current_path = input.substr(current, processed);
    current += processed;
    return current;
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_authority(const view_type& input)
{
    basic_authority_reader<value_type> reader(input);

    typename view_type::const_iterator end = input.begin();
    do
    {
        end = reader.literal().end();
    } while (reader.next());

    return std::distance(input.begin(), end);
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_path(const view_type& input)
{
    basic_path_reader<value_type> reader(input);

    typename view_type::const_iterator end = input.begin();
    do
    {
        end = reader.literal().end();
    } while (reader.next());

    return std::distance(input.begin(), end);
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_query(const view_type& input)
{
    // RFC 3986 Section 3.4
    //
    // query = *( pchar / "/" / "?" )

    typename view_type::const_iterator current = input.begin();
    while (current != input.end())
    {
        std::size_t processed = syntax::pchar<value_type>::match(&*current);
        if (processed == 0)
        {
            if ((*current == syntax::character<value_type>::alpha_slash) ||
                (*current == syntax::character<value_type>::alpha_question_mark))
            {
                processed = 1;
            }
            else
            {
                break;
            }
        }
        current += processed;
    }
    const std::size_t result = std::distance(input.begin(), current);
    current_query = input.substr(0, result);
    return result;
}

template <typename CharT>
std::size_t basic_parser<CharT>::parse_fragment(const view_type& input)
{
    // RFC 3986 Section 3.5
    // 
    // fragment = *( pchar / "/" / "?" )

    typename view_type::const_iterator current = input.begin();
    while (current != input.end())
    {
        std::size_t processed = syntax::pchar<value_type>::match(&*current);
        if (processed == 0)
        {
            if ((*current == syntax::character<value_type>::alpha_slash) ||
                (*current == syntax::character<value_type>::alpha_question_mark))
            {
                processed = 1;
            }
            else
            {
                break;
            }
        }
        current += processed;
    }
    const std::size_t result = std::distance(input.begin(), current);
    current_fragment = input.substr(0, result);
    return result;
}

} // namespace url
} // namespace trial

#endif // TRIAL_URL_PARSER_IPP
