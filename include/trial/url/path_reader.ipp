#ifndef TRIAL_URL_PATH_READER_IPP
#define TRIAL_URL_PATH_READER_IPP

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
#include <trial/url/syntax/segment.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
basic_path_reader<CharT>::basic_path_reader(const view_type& view)
    : input(view)
{
    first();
}

template <typename CharT>
const typename basic_path_reader<CharT>::view_type&
basic_path_reader<CharT>::literal_segment() const
{
    return current_segment;
}

template <typename CharT>
typename basic_path_reader<CharT>::string_type
basic_path_reader<CharT>::segment() const
{
    return syntax::segment<value_type>::decode(current_segment);
}

template <typename CharT>
bool basic_path_reader<CharT>::next()
{
    return (this->*next_state)();
}

template <typename CharT>
void basic_path_reader<CharT>::first()
{
    if (input.empty())
    {
        current_segment = input;
        next_state = &basic_path_reader<value_type>::next_done;
    }
    else if (input.front() == syntax::character<value_type>::alpha_slash)
    {
        next_state = &basic_path_reader<value_type>::next_abempty;
        next();
    }
    else
    {
        next_state = &basic_path_reader<value_type>::next_done;
    }
}

template <typename CharT>
bool basic_path_reader<CharT>::next_done()
{
    current_segment = input;
    return false;
}

template <typename CharT>
bool basic_path_reader<CharT>::next_abempty()
{
    // RFC 3986, section 3.3
    //
    // path-abempty  = *( "/" segment )

    if (!input.empty() &&
        (input.front() == syntax::character<value_type>::alpha_slash))
    {
        input.remove_prefix(1);
        std::size_t processed = syntax::segment<value_type>::match(input);
        current_segment = input.substr(0, processed);
        input.remove_prefix(processed);
        return true;
    }
    else
    {
        next_state = &basic_path_reader<value_type>::next_done;
        return false;
    }
}

} // namespace url
} // namespace trial

#endif // TRIAL_URL_PATH_READER_IPP
