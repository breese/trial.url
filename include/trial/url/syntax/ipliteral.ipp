#ifndef TRIAL_URL_SYNTAX_IPLITERAL_IPP
#define TRIAL_URL_SYNTAX_IPLITERAL_IPP

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
#include <trial/url/syntax/ipv6address.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t ipliteral<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // IP-literal = "[" ( IPv6address / IPvFuture  ) "]"

    typename view_type::const_iterator current = view.begin();
    if (*current != syntax::character<value_type>::alpha_bracket_open)
        return 0;
    ++current;

    std::size_t processed = syntax::ipv6address<value_type>::match(&*current);
    if (processed == 0)
    {
        // FIXME: IPvFuture
        return 0;
    }
    current += processed;
    if (*current != syntax::character<value_type>::alpha_bracket_close)
        return 0;
    ++current;

    return std::distance(view.begin(), current);
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_IPLITERAL_IPP
