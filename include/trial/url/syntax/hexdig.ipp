#ifndef TRIAL_URL_SYNTAX_HEXDIG_IPP
#define TRIAL_URL_SYNTAX_HEXDIG_IPP

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

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t hexdig<CharT>::match(value_type value)
{
    // RFC 2234 Section 6.1
    //
    // HEXDIG =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"

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
    case character<value_type>::alpha_A:
    case character<value_type>::alpha_a:
    case character<value_type>::alpha_B:
    case character<value_type>::alpha_b:
    case character<value_type>::alpha_C:
    case character<value_type>::alpha_c:
    case character<value_type>::alpha_D:
    case character<value_type>::alpha_d:
    case character<value_type>::alpha_E:
    case character<value_type>::alpha_e:
    case character<value_type>::alpha_F:
    case character<value_type>::alpha_f:
        return true;
    default:
        return false;
    }
}

template <typename CharT>
typename hexdig<CharT>::int_type hexdig<CharT>::decode(value_type value)
{
    switch (value)
    {
    case character<value_type>::alpha_0:
        return 0;
    case character<value_type>::alpha_1:
        return 1;
    case character<value_type>::alpha_2:
        return 2;
    case character<value_type>::alpha_3:
        return 3;
    case character<value_type>::alpha_4:
        return 4;
    case character<value_type>::alpha_5:
        return 5;
    case character<value_type>::alpha_6:
        return 6;
    case character<value_type>::alpha_7:
        return 7;
    case character<value_type>::alpha_8:
        return 8;
    case character<value_type>::alpha_9:
        return 9;
    case character<value_type>::alpha_A:
    case character<value_type>::alpha_a:
        return 10;
    case character<value_type>::alpha_B:
    case character<value_type>::alpha_b:
        return 11;
    case character<value_type>::alpha_C:
    case character<value_type>::alpha_c:
        return 12;
    case character<value_type>::alpha_D:
    case character<value_type>::alpha_d:
        return 13;
    case character<value_type>::alpha_E:
    case character<value_type>::alpha_e:
        return 14;
    case character<value_type>::alpha_F:
    case character<value_type>::alpha_f:
        return 15;
    default:
        assert(false);
        return 0;
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_HEXDIG_IPP
