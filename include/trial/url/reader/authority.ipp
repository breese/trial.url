#ifndef TRIAL_URL_READER_AUTHORITY_IPP
#define TRIAL_URL_READER_AUTHORITY_IPP

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
#include <trial/url/syntax/userinfo.hpp>
#include <trial/url/syntax/ipliteral.hpp>
#include <trial/url/syntax/ipv4address.hpp>
#include <trial/url/syntax/regname.hpp>
#include <trial/url/syntax/port.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
basic_authority<CharT>::basic_authority(const view_type& view)
    : input(view),
      current_token(token::subcode::end),
      current_view(view)
{
    first();
}

template <typename CharT>
token::category::value basic_authority<CharT>::category() const
{
    return token::category(code());
}

template <typename CharT>
token::code::value basic_authority<CharT>::code() const
{
    return token::code(subcode());
}

template <typename CharT>
token::subcode::value basic_authority<CharT>::subcode() const
{
    return current_token;
}

template <typename CharT>
const typename basic_authority<CharT>::view_type&
basic_authority<CharT>::literal() const
{
    return current_view;
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_authority<CharT>::value() const
{
    // FIXME: Via converter
    return ReturnType(current_view.begin(),
                      current_view.end());
}

template <typename CharT>
const typename basic_authority<CharT>::view_type&
basic_authority<CharT>::tail() const
{
    return input;
}

template <typename CharT>
void basic_authority<CharT>::reset(const view_type& view)
{
    input = current_view = view;
    current_token = token::subcode::end;
    first();
}

template <typename CharT>
void basic_authority<CharT>::first()
{
    next();
}

template <typename CharT>
bool basic_authority<CharT>::next()
{
    // RFC 3986 Section 3.2
    //
    // authority = [ userinfo "@" ] host [ ":" port ]

    if (input.empty())
    {
        current_token = token::subcode::end;
        return false;
    }

    switch (code())
    {
    case token::code::end:
        current_token = next_userinfo();
        if (code() == token::code::end)
            current_token = next_host();
        break;

    case token::code::authority_userinfo:
        current_token = next_host();
        break;

    case token::code::authority_host:
        current_token = next_port();
        break;

    case token::code::authority_port:
        current_token = token::subcode::end;
        break;

    default:
        current_token = token::subcode::unknown;
        break;
    }
    return (category() != token::category::error);
}

template <typename CharT>
token::subcode::value basic_authority<CharT>::next_userinfo()
{
    std::size_t processed = syntax::userinfo<value_type>::match(input);
    if (input[processed] == syntax::character<value_type>::alpha_at)
    {
        current_view = input.substr(0, processed);
        input = input.substr(processed + 1);
        return token::subcode::authority_userinfo;
    }
    return token::subcode::end;
}

template <typename CharT>
token::subcode::value basic_authority<CharT>::next_host()
{
    // RFC 3986 Section 3.2.2
    //
    // host = IP-literal / IPv4address / reg-name

    token::subcode::value result = token::subcode::end;
    std::size_t processed = 0;

    if (input.front() == syntax::character<value_type>::alpha_bracket_open)
    {
        processed = syntax::ipliteral<value_type>::match(input);
        if (processed < 2)
            return result;
        // Skip brackets
        current_view = input.substr(1, processed - 2);
        input = input.substr(processed);
        result = token::subcode::authority_host_ipv6;
    }
    else
    {
        processed = syntax::ipv4address<value_type>::match(input);
        if (processed == 0)
        {
            processed = syntax::regname<value_type>::match(input);
            if (processed == 0)
                return result;
            result = token::subcode::authority_host_name;
        }
        else
        {
            result = token::subcode::authority_host_ipv4;
        }
        current_view = input.substr(0, processed);
        input = input.substr(processed);
    }

    return result;
}

template <typename CharT>
token::subcode::value basic_authority<CharT>::next_port()
{
    if (input.front() == syntax::character<value_type>::alpha_colon)
    {
        input.remove_prefix(1);
        std::size_t processed = syntax::port<value_type>::match(input);
        if (processed > 0)
        {
            current_view = input.substr(0, processed);
            input = input.substr(processed);
            return token::subcode::authority_port;
        }
    }
    return token::subcode::end;
}

} // namespace reader
} // namespace url
} // namespace trial

#endif // TRIAL_URL_READER_AUTHORITY_IPP
