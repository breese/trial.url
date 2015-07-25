#ifndef TRIAL_URL_SYNTAX_DEC_OCTET_IPP
#define TRIAL_URL_SYNTAX_DEC_OCTET_IPP

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

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t dec_octet<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.2
    //
    // dec-octet   = DIGIT                 ; 0-9
    //             / %x31-39 DIGIT         ; 10-99
    //             / "1" 2DIGIT            ; 100-199
    //             / "2" %x30-34 DIGIT     ; 200-249
    //             / "25" %x30-35          ; 250-255
    switch (view[0])
    {
    case syntax::character<value_type>::alpha_0:
        return 1;

    case syntax::character<value_type>::alpha_1:
        if ((view.size() <= 1) || (syntax::digit<value_type>::match(view[1]) == 0))
            return 1;
        if ((view.size() <= 2) || (syntax::digit<value_type>::match(view[2]) == 0))
            return 2;
        return 3;

    case syntax::character<value_type>::alpha_2:
        if (view.size() <= 1)
            return 1;
        switch (view[1])
        {
        case syntax::character<value_type>::alpha_0:
        case syntax::character<value_type>::alpha_1:
        case syntax::character<value_type>::alpha_2:
        case syntax::character<value_type>::alpha_3:
        case syntax::character<value_type>::alpha_4:
            if ((view.size() > 2) && (syntax::digit<value_type>::match(view[2]) > 0))
                return 3;
            return 2;

        case syntax::character<value_type>::alpha_5:
            if (view.size() <= 2)
                return 2;
            switch (view[2])
            {
            case syntax::character<value_type>::alpha_0:
            case syntax::character<value_type>::alpha_1:
            case syntax::character<value_type>::alpha_2:
            case syntax::character<value_type>::alpha_3:
            case syntax::character<value_type>::alpha_4:
            case syntax::character<value_type>::alpha_5:
                return 3;
            default:
                return 0;
            }

        default:
            return 1;
        }

    case syntax::character<value_type>::alpha_3:
    case syntax::character<value_type>::alpha_4:
    case syntax::character<value_type>::alpha_5:
    case syntax::character<value_type>::alpha_6:
    case syntax::character<value_type>::alpha_7:
    case syntax::character<value_type>::alpha_8:
    case syntax::character<value_type>::alpha_9:
        if (view.size() <= 1)
            return 1;
        if (syntax::digit<value_type>::match(view[1]) > 0)
            return 2;
        return 1;

    default:
        return 0;
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_DEC_OCTET_IPP
