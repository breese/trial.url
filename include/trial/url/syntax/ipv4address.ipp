#ifndef TRIAL_URL_SYNTAX_IPV4ADDRESS_IPP
#define TRIAL_URL_SYNTAX_IPV4ADDRESS_IPP

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
#include <trial/url/syntax/dec_octet.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t ipv4address<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet

    // First octet
    std::size_t processed = syntax::dec_octet<value_type>::match(view);
    std::size_t total = processed;
    if ((processed == 0) || (view[total] != syntax::character<value_type>::alpha_dot))
        return 0;
    total += sizeof(syntax::character<value_type>::alpha_dot);

    // Second octet
    processed = syntax::dec_octet<value_type>::match(view.substr(total));
    total += processed;
    if ((processed == 0) || (view[total] != syntax::character<value_type>::alpha_dot))
        return 0;
    total += sizeof(syntax::character<value_type>::alpha_dot);

    // Third octet
    processed = syntax::dec_octet<value_type>::match(view.substr(total));
    total += processed;
    if ((processed == 0) || (view[total] != syntax::character<value_type>::alpha_dot))
        return 0;
    total += sizeof(syntax::character<value_type>::alpha_dot);

    // Fourth octet
    processed = syntax::dec_octet<value_type>::match(view.substr(total));
    if (processed == 0)
        return 0;
    total += processed;

    return total;
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_IPV4ADDRESS_IPP
