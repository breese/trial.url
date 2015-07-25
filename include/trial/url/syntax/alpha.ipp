#ifndef TRIAL_URL_SYNTAX_ALPHA_IPP
#define TRIAL_URL_SYNTAX_ALPHA_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t alpha<CharT>::match(value_type value)
{
    // RFC 2234 Section 6.1
    //
    // ALPHA = %x41-5A / %x61-7A  ; A-Z / a-z

    if ((value >= character<value_type>::alpha_A) &&
        (value <= character<value_type>::alpha_Z))
        return true;
    if ((value >= character<value_type>::alpha_a) &&
        (value <= character<value_type>::alpha_z))
        return true;
    return false;
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_ALPHA_IPP
