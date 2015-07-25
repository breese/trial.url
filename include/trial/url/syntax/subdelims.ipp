#ifndef TRIAL_URL_SYNTAX_SUBDELIMS_IPP
#define TRIAL_URL_SYNTAX_SUBDELIMS_IPP

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
std::size_t subdelims<CharT>::match(value_type value)
{
    // RFC 3986 Section 2.2
    //
    // sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="

    switch (value)
    {
    case character<value_type>::alpha_exclamation:
    case character<value_type>::alpha_dollar:
    case character<value_type>::alpha_ampersand:
    case character<value_type>::alpha_apostrophe:
    case character<value_type>::alpha_parens_open:
    case character<value_type>::alpha_parens_close:
    case character<value_type>::alpha_asterisk:
    case character<value_type>::alpha_plus:
    case character<value_type>::alpha_comma:
    case character<value_type>::alpha_semicolon:
    case character<value_type>::alpha_equal:
        return 1;

    default:
        return 0;
    }
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_SUBDELIMS_IPP
