#ifndef TRIAL_URL_SYNTAX_PCHAR_IPP
#define TRIAL_URL_SYNTAX_PCHAR_IPP

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
std::size_t pchar<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.3
    //
    // pchar = unreserved / pct-encoded / sub-delims / ":" / "@"

    switch (view.front())
    {
    case syntax::character<value_type>::alpha_percent:
        return syntax::pct_encoded<value_type>::match(view);

    case syntax::character<value_type>::alpha_colon:
    case syntax::character<value_type>::alpha_at:
        return 1;

    default:
        if ((syntax::unreserved<value_type>::match(view.front()) == 1) ||
            (syntax::subdelims<value_type>::match(view.front()) == 1))
            return 1;
        return 0;
    }
}

template <typename CharT>
typename pchar<CharT>::value_type pchar<CharT>::decode(const view_type& view)
{
    assert(match(view) > 0);

    switch (view.front())
    {
    case syntax::character<value_type>::alpha_percent:
        return syntax::pct_encoded<value_type>::decode(view);

    default:
        return view.front();
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_PCHAR_IPP
