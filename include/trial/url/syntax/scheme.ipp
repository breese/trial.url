#ifndef TRIAL_URL_SYNTAX_SCHEME_IPP
#define TRIAL_URL_SYNTAX_SCHEME_IPP

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
#include <trial/url/syntax/digit.hpp>
#include <trial/url/syntax/alpha.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t scheme<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.1
    //
    // scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )

    std::size_t current = 0;

    if (view.empty())
        return current;

    if (syntax::alpha<value_type>::match(view[current]) == 0)
        return 0;
    ++current;

    for (;
         current < view.size();
         ++current)
    {
        if (!is_valid(view[current]))
            break;
    }
    return current;
}

template <typename CharT>
bool scheme<CharT>::is_valid(value_type value)
{
    // RFC 3986 Section 3.1
    //
    // Optional part of scheme.
    //
    // ALPHA / DIGIT / "+" / "-" / "."

    switch (value)
    {
    case character<value_type>::alpha_plus:
    case character<value_type>::alpha_minus:
    case character<value_type>::alpha_dot:
        return true;

    default:
        return ((syntax::digit<value_type>::match(value) > 0) ||
                (syntax::alpha<value_type>::match(value) > 0));
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_SCHEME_IPP
