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

#include <trial/url/syntax/character.hpp>
#include <trial/url/syntax/digit.hpp>
#include <trial/url/syntax/subdelims.hpp>
#include <trial/url/syntax/unreserved.hpp>
#include <trial/url/syntax/pct_encoded.hpp>

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

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_PORT_IPP
