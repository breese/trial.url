#ifndef TRIAL_URL_SYNTAX_SEGMENT_IPP
#define TRIAL_URL_SYNTAX_SEGMENT_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <trial/url/syntax/pchar.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
std::size_t segment<CharT>::match(const view_type& view)
{
    // RFC 3986, section 3.3
    //
    // segment       = *pchar

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator current = begin;
    while (current != end)
    {
        std::size_t processed = syntax::pchar<value_type>::match(&*current);
        if (processed == 0)
            break;
        current += processed;
    }
    return std::distance(begin, current);
}

template <typename CharT>
typename segment<CharT>::string_type
segment<CharT>::decode(const view_type& view)
{
    string_type result;
    for (typename view_type::const_iterator current = view.begin();
         current != view.end();
         ++current)
    {
        std::size_t processed = syntax::pchar<value_type>::match(&*current);
        if (processed == 0)
            break;
        result += syntax::pchar<value_type>::decode(&*current);
        current += (processed - 1);
    }
    return result;
}

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_SEGMENT_IPP
