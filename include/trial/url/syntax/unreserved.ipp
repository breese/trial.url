#ifndef TRIAL_URL_SYNTAX_UNRESERVED_IPP
#define TRIAL_URL_SYNTAX_UNRESERVED_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/url/syntax/digit.hpp>
#include <trial/url/syntax/alpha.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t unreserved<CharT>::match(value_type value) BOOST_NOEXCEPT
{
    // RFC 3986 Section 2.3
    //
    // unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"

    switch (value)
    {
    case character<value_type>::alpha_minus:
    case character<value_type>::alpha_dot:
    case character<value_type>::alpha_underscore:
    case character<value_type>::alpha_tilde:
        return 1;

    default:
        if (digit<value_type>::match(value) ||
            alpha<value_type>::match(value))
            return 1;
        return 0;
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_UNRESERVED_IPP
