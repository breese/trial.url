#ifndef TRIAL_URL_SYNTAX_QUERY_IPP
#define TRIAL_URL_SYNTAX_QUERY_IPP

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
#include <trial/url/syntax/pchar.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t query<CharT>::match(const view_type& view)
{
    // RFC 3986 Section 3.4
    //
    // query = *( pchar / "/" / "?" )

    typename view_type::const_iterator current = view.begin();
    while (current != view.end())
    {
        std::size_t processed = syntax::pchar<value_type>::match(&*current);
        if (processed == 0)
        {
            if ((*current == syntax::character<value_type>::alpha_slash) ||
                (*current == syntax::character<value_type>::alpha_question_mark))
            {
                processed = 1;
            }
            else
            {
                break; // while
            }
        }
        current += processed;
    }
    return std::distance(view.begin(), current);
}

} // namespace syntax
} // namespace url
} // namespace trial


#endif // TRIAL_URL_SYNTAX_QUERY_IPP
