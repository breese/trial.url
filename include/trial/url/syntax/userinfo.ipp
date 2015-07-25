#ifndef TRIAL_URL_SYNTAX_USERINFO_IPP
#define TRIAL_URL_SYNTAX_USERINFO_IPP

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
std::size_t userinfo<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.2.1
    //
    // userinfo = *( unreserved / pct-encoded / sub-delims / ":" )

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;
    for (; current != end; ++current)
    {
        switch (*current)
        {
        case syntax::character<value_type>::alpha_percent:
            {
                std::size_t processed = syntax::pct_encoded<value_type>::match(&*current);
                if (processed == 0)
                    return 0;
                current += (processed - 1);
            }
            break;

        case syntax::character<value_type>::alpha_colon:
            break;

        default:
            if ((syntax::unreserved<value_type>::match(*current) == 1) ||
                (syntax::subdelims<value_type>::match(*current) == 1))
            {
            }
            else
            {
                return std::distance(begin, current);
            }
            break;
        }
    }
    return std::distance(begin, current);
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_USERINFO_IPP
