#ifndef TRIAL_URL_READER_PATH_IPP
#define TRIAL_URL_READER_PATH_IPP

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
namespace reader
{

template <typename CharT>
basic_path<CharT>::basic_path(const view_type& view)
    : input(view),
      current_token(token::subcode::end),
      current_view(view)
{
    first();
}

template <typename CharT>
token::category::value basic_path<CharT>::category() const
{
    return token::category(code());
}

template <typename CharT>
token::code::value basic_path<CharT>::code() const
{
    return token::code(subcode());
}

template <typename CharT>
token::subcode::value basic_path<CharT>::subcode() const
{
    return current_token;
}

template <typename CharT>
const typename basic_path<CharT>::view_type&
basic_path<CharT>::literal() const
{
    return current_view;
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_path<CharT>::value() const
{
    return syntax::segment<value_type>::decode(current_view);
}

template <typename CharT>
const typename basic_path<CharT>::view_type&
basic_path<CharT>::tail() const
{
    return input;
}

template <typename CharT>
void basic_path<CharT>::reset(const view_type& view)
{
    input = current_view = view;
    current_token = token::subcode::end;
    first();
}

template <typename CharT>
bool basic_path<CharT>::next()
{
    current_token = (this->*next_state)();
    return category() != token::category::error;
}

template <typename CharT>
void basic_path<CharT>::first()
{
    if (input.empty())
    {
        current_view = input;
        current_token = token::subcode::end;
        next_state = &basic_path<value_type>::next_done;
    }
    else if (input.front() == syntax::character<value_type>::alpha_slash)
    {
        next_state = &basic_path<value_type>::next_abempty;
        next();
    }
    else
    {
        next_state = &basic_path<value_type>::next_done;
    }
}

template <typename CharT>
token::subcode::value basic_path<CharT>::next_done()
{
    current_view = input;
    return token::subcode::end;
}

template <typename CharT>
token::subcode::value basic_path<CharT>::next_abempty()
{
    // RFC 3986, section 3.3
    //
    // path-abempty  = *( "/" segment )

    if (!input.empty() &&
        (input.front() == syntax::character<value_type>::alpha_slash))
    {
        input.remove_prefix(1);
        std::size_t processed = syntax::segment<value_type>::match(input);
        current_view = input.substr(0, processed);
        input.remove_prefix(processed);
        return token::subcode::path_segment;
    }
    else
    {
        next_state = &basic_path<value_type>::next_done;
        return next_done();
    }
}

} // namespace reader
} // namespace url
} // namespace trial

#endif // TRIAL_URL_READER_PATH_IPP
