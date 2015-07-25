#ifndef TRIAL_URL_SYNTAX_PCT_ENCODED_IPP
#define TRIAL_URL_SYNTAX_PCT_ENCODED_IPP

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
#include <string>
#include <trial/url/syntax/hexdig.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t pct_encoded<CharT>::match(const view_type& view)
{
    // pct-encoded = "%" HEXDIG HEXDIG

    const std::size_t size = 3;

    if (view.size() < size)
        return 0;

    if (view[0] != syntax::character<value_type>::alpha_percent)
        return 0;

    if (syntax::hexdig<value_type>::match(view[1]) == 0)
        return 0;

    if (syntax::hexdig<value_type>::match(view[2]) == 0)
        return 0;

    return size;
}


template <typename CharT>
typename pct_encoded<CharT>::value_type pct_encoded<CharT>::decode(const view_type& view)
{
    assert(match(view) == 3);

    typename syntax::hexdig<value_type>::int_type number = syntax::hexdig<value_type>::decode(view[1]) << 4;
    number += syntax::hexdig<value_type>::decode(view[2]);
    return std::char_traits<value_type>::to_char_type(number);
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_PCT_ENCODED_IPP
