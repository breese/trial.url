#ifndef TRIAL_URL_SYNTAX_PORT_IPP
#define TRIAL_URL_SYNTAX_PORT_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <trial/url/syntax/character.hpp>
#include <trial/url/syntax/digit.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t port<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.3
    //
    // port = *DIGIT

    typename view_type::const_iterator current = view.begin();
    while (current != view.end())
    {
        if (!syntax::digit<value_type>::match(*current))
            break;
        ++current;
    }
    return std::distance(view.begin(), current);
}

template <typename CharT>
template <typename T>
auto port<CharT>::decode(const view_type& view) -> T
{
    T result = T(0);
    typename view_type::const_iterator current = view.begin();
    while (current != view.end())
    {
        if (!syntax::digit<value_type>::match(*current))
            break;
        result *= T(10);
        switch (*current)
        {
        case character<value_type>::alpha_0:
            break;
        case character<value_type>::alpha_1:
            result += T(1);
            break;
        case character<value_type>::alpha_2:
            result += T(2);
            break;
        case character<value_type>::alpha_3:
            result += T(3);
            break;
        case character<value_type>::alpha_4:
            result += T(4);
            break;
        case character<value_type>::alpha_5:
            result += T(5);
            break;
        case character<value_type>::alpha_6:
            result += T(6);
            break;
        case character<value_type>::alpha_7:
            result += T(7);
            break;
        case character<value_type>::alpha_8:
            result += T(8);
            break;
        case character<value_type>::alpha_9:
            result += T(9);
            break;
        default:
            assert(false);
            break;
        }
        ++current;
    }
    return result;
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_PORT_IPP
