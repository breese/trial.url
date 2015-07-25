#ifndef TRIAL_URL_AUTHORITY_PARSER_IPP
#define TRIAL_URL_AUTHORITY_PARSER_IPP

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
#include <trial/url/syntax/userinfo.hpp>
#include <trial/url/syntax/ipliteral.hpp>
#include <trial/url/syntax/ipv4address.hpp>
#include <trial/url/syntax/regname.hpp>
#include <trial/url/syntax/port.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
basic_authority_parser<CharT>::basic_authority_parser(const view_type& view)
{
    parse(view);
}

template <typename CharT>
const typename basic_authority_parser<CharT>::view_type&
basic_authority_parser<CharT>::authority() const
{
    return current_authority;
}

template <typename CharT>
const typename basic_authority_parser<CharT>::view_type&
basic_authority_parser<CharT>::userinfo() const
{
    return current_userinfo;
}

template <typename CharT>
const typename basic_authority_parser<CharT>::view_type&
basic_authority_parser<CharT>::host() const
{
    return current_host;
}

template <typename CharT>
const typename basic_authority_parser<CharT>::view_type&
basic_authority_parser<CharT>::port() const
{
    return current_port;
}

template <typename CharT>
std::size_t basic_authority_parser<CharT>::parse(const view_type& view)
{
    // RFC 3986 Section 3.2
    //
    // authority = [ userinfo "@" ] host [ ":" port ]

    std::size_t processed = syntax::userinfo<value_type>::match(view);
    std::size_t total = 0;
    view_type input = view;
    if (view[processed] == syntax::character<value_type>::alpha_at)
    {
        current_userinfo = view.substr(0, processed);
        total += processed + 1;
        input = view.substr(processed + 1);
    }

    processed = parse_host(input);
    if (processed == 0)
        return 0;
    total += processed;

    if (input[processed] == syntax::character<value_type>::alpha_colon)
    {
        ++total;
        processed = syntax::port<value_type>::match(view.substr(total, processed));
        if (processed > 0)
        {
            current_port = view.substr(total, processed);
            total += processed;
        }
    }
    current_authority = view.substr(0, total);
    return total;
}

template <typename CharT>
std::size_t basic_authority_parser<CharT>::parse_host(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // host = IP-literal / IPv4address / reg-name

    std::size_t processed = 0;

    if (view.front() == syntax::character<value_type>::alpha_bracket_open)
    {
        processed = syntax::ipliteral<value_type>::match(view);
        if (processed < 2)
            return 0;
        // Skip brackets
        current_host = view.substr(1, processed - 2);
    }
    else
    {
        processed = syntax::ipv4address<value_type>::match(view);
        if (processed == 0)
        {
            processed = syntax::regname<value_type>::match(view);
            if (processed == 0)
                return 0;
        }
        current_host = view.substr(0, processed);
    }

    return processed;
}

} // namespace url
} // namespace trial

#endif // TRIAL_URL_AUTHORITY_PARSER_IPP
