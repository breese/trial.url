#ifndef TRIAL_URL_SYNTAX_DIGIT_IPP
#define TRIAL_URL_SYNTAX_DIGIT_IPP

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
std::size_t digit<CharT>::match(value_type value)
{
    // RFC 2234 Section 6.1
    //
    // DIGIT =  %x30-39 ; 0-9

    switch (value)
    {
    case character<value_type>::alpha_0:
    case character<value_type>::alpha_1:
    case character<value_type>::alpha_2:
    case character<value_type>::alpha_3:
    case character<value_type>::alpha_4:
    case character<value_type>::alpha_5:
    case character<value_type>::alpha_6:
    case character<value_type>::alpha_7:
    case character<value_type>::alpha_8:
    case character<value_type>::alpha_9:
        return 1;

    default:
        return 0;
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_DIGIT_IPP
