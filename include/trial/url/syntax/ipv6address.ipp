#ifndef TRIAL_URL_SYNTAX_IPV6ADDRESS_IPP
#define TRIAL_URL_SYNTAX_IPV6ADDRESS_IPP

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
#include <trial/url/syntax/hexdig.hpp>
#include <trial/url/syntax/ipv4address.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t ipv6address<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // IPv6address =                            6( h16 ":" ) ls32
    //             /                       "::" 5( h16 ":" ) ls32
    //             / [               h16 ] "::" 4( h16 ":" ) ls32
    //             / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
    //             / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
    //             / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
    //             / [ *4( h16 ":" ) h16 ] "::"              ls32
    //             / [ *5( h16 ":" ) h16 ] "::"              h16
    //             / [ *6( h16 ":" ) h16 ] "::"

    std::size_t processed = match_alternative_1(view);
    if (processed > 0)
        return processed;

    processed = match_alternative_2(view);
    if (processed > 0)
        return processed;

    processed = match_alternative_3(view, 1, 4);
    if (processed > 0)
        return processed;

    processed = match_alternative_3(view, 2, 3);
    if (processed > 0)
        return processed;

    processed = match_alternative_3(view, 3, 2);
    if (processed > 0)
        return processed;

    processed = match_alternative_3(view, 4, 1);
    if (processed > 0)
        return processed;

    processed = match_alternative_3(view, 5, 0);
    if (processed > 0)
        return processed;

    processed = match_alternative_4(view);
    if (processed > 0)
        return processed;

    processed = match_alternative_5(view);
    if (processed > 0)
        return processed;

    return 0;
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_alternative_1(const view_type& view)
{
    // See match
    //
    // 6( h16 ":" ) ls32

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;

    std::size_t processed = 0;
    for (std::size_t after = 0; after < 6; ++after)
    {
        processed = match_h16(&*current);
        if (processed == 0)
            return 0;
        current += processed;
        if (current == end || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
    }

    processed = match_ls32(&*current);
    if (processed == 0)
        return 0;
    current += processed;

    return std::distance(begin, current);
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_alternative_2(const view_type& view)
{
    // See match
    //
    // "::" 5( h16 ":" ) ls32

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;

    if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
        return 0;
    ++current;
    if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
        return 0;
    ++current;

    std::size_t processed = 0;
    for (std::size_t after = 0; after < 5; ++after)
    {
        processed = match_h16(&*current);
        if (processed == 0)
            return 0;
        current += processed;
        if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
    }

    processed = match_ls32(&*current);
    if (processed == 0)
        return 0;
    current += processed;
    
    return std::distance(begin, current);
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_alternative_3(const view_type& view,
                                                    std::size_t beforeLimit,
                                                    std::size_t afterLimit)
{
    // See match
    //
    // [ h16 ] "::" 4( h16 ":" ) ls32
    // [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
    // [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
    // [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;

    std::size_t processed = 0;
    for (std::size_t before = 0; before < beforeLimit; ++before)
    {
        processed = match_h16(&*current);
        current += processed;
        if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
        if (*current == syntax::character<value_type>::alpha_colon)
            break;
    }
    if (*current != syntax::character<value_type>::alpha_colon)
        return 0;
    ++current;

    for (std::size_t after = 0; after < afterLimit; ++after)
    {
        processed = match_h16(&*current);
        if (processed == 0)
            return 0;
        current += processed;
        if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
    }

    processed = match_ls32(&*current);
    if (processed == 0)
        return 0;
    current += processed;
    
    return std::distance(begin, current);
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_alternative_4(const view_type& view)
{
    // See match
    //
    // [ *5( h16 ":" ) h16 ] "::"              h16

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;

    std::size_t processed = 0;
    for (std::size_t before = 0; before < 6; ++before)
    {
        processed = match_h16(&*current);
        current += processed;
        if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
        if (*current == syntax::character<value_type>::alpha_colon)
            break;
    }
    if (*current != syntax::character<value_type>::alpha_colon)
        return 0;
    ++current;

    processed = match_h16(&*current);
    if (processed == 0)
        return 0;
    current += processed;
    
    return std::distance(begin, current);
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_alternative_5(const view_type& view)
{
    // See match
    //
    // [ *6( h16 ":" ) h16 ] "::"

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;

    std::size_t processed = 0;
    for (std::size_t before = 0; before < 7; ++before)
    {
        processed = match_h16(&*current);
        current += processed;
        if ((current == end) || (*current != syntax::character<value_type>::alpha_colon))
            return 0;
        ++current;
        if (current == end)
            return 0;
        if (*current == syntax::character<value_type>::alpha_colon)
            break;
    }
    if (*current != syntax::character<value_type>::alpha_colon)
        return 0;
    ++current;

    return std::distance(begin, current);
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_h16(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // h16         = 1*4HEXDIG
    //             ; 16 bits of address represented in hexadecimal

    if (view.size() < 4)
        return 0;

    if (syntax::hexdig<value_type>::match(view[0]) == 0)
        return 0;
    if (syntax::hexdig<value_type>::match(view[1]) == 0)
        return 1;
    if (syntax::hexdig<value_type>::match(view[2]) == 0)
        return 2;
    if (syntax::hexdig<value_type>::match(view[3]) == 0)
        return 3;
    return 4;
}

template <typename CharT>
std::size_t ipv6address<CharT>::match_ls32(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // ls32        = ( h16 ":" h16 ) / IPv4address
    //             ; least-significant 32 bits of address

    typename view_type::const_iterator current = view.begin();
    std::size_t processed = syntax::ipv4address<value_type>::match(&*current);
    if (processed > 0)
        return processed;

    processed = match_h16(&*current);
    if (processed == 0)
        return 0;
    current += processed;
    if (*current != syntax::character<value_type>::alpha_colon)
        return 0;
    ++current;
    processed = match_h16(&*current);
    if (processed == 0)
        return 0;
    current += processed;
    return std::distance(view.begin(), current);
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_IPV6ADDRESS_IPP
