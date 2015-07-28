#ifndef TRIAL_URL_READER_URL_IPP
#define TRIAL_URL_READER_URL_IPP

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
#include <trial/url/syntax/scheme.hpp>
#include <trial/url/syntax/query.hpp>
#include <trial/url/syntax/fragment.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
basic_url<CharT>::basic_url(const view_type& view)
    : input(view),
      current_token(token::subcode::end),
      current_view(view),
      authority_reader(view),
      path_reader(view)
{
    first();
}

template <typename CharT>
token::category::value basic_url<CharT>::category() const
{
    return token::category(code());
}

template <typename CharT>
token::code::value basic_url<CharT>::code() const
{
    return token::code(subcode());
}

template <typename CharT>
token::subcode::value basic_url<CharT>::subcode() const
{
    return current_token;
}

template <typename CharT>
const typename basic_url<CharT>::view_type&
basic_url<CharT>::literal() const
{
    return current_view;
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_url<CharT>::value() const
{
    return ReturnType(current_view.begin(),
                      current_view.end());
}

template <typename CharT>
void basic_url<CharT>::first()
{
    next();
}

template <typename CharT>
bool basic_url<CharT>::next()
{
    // RFC 3986 Section 3
    //
    // URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

    if (input.empty())
    {
        current_token = token::subcode::end;
        return false;
    }

    switch (category())
    {
    case token::category::error:
        if (subcode() == token::subcode::end)
            current_token = next_scheme();
        break;

    case token::category::scheme:
        current_token = next_hier_part();
        break;

    case token::category::authority:
        current_token = next_authority();
        if (subcode() == token::subcode::end)
        {
            path_reader.reset(input);
            current_token = next_path();
        }
        break;

    case token::category::path:
        current_token = next_path();
        if (subcode() != token::subcode::end)
            break;
        current_token = next_query();
        if (subcode() != token::subcode::end)
            break;
        // FALLTHROUGH
    case token::category::query:
        current_token = next_fragment();
        break;

    default:
        current_token = token::subcode::end;
        break;
    }
    return (category() != token::category::error);
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_scheme()
{
    std::size_t processed = syntax::scheme<value_type>::match(input);
    if (processed > 0)
    {
        if ((input.size() > processed) &&
            (input[processed] == syntax::character<value_type>::alpha_colon))
        {
            current_view = input.substr(0, processed);
            input = input.substr(processed + 1);
            return token::subcode::scheme;
        }
    }
    return token::subcode::end;
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_hier_part()
{
    if ((input.size() >= 2) &&
        (input[0] == syntax::character<value_type>::alpha_slash) &&
        (input[1] == syntax::character<value_type>::alpha_slash))
    {
        input.remove_prefix(2);
        authority_reader.reset(input);
        return next_authority();
    }
    return token::subcode::end;
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_authority()
{
    token::subcode::value result = token::subcode::end;
    switch (authority_reader.category())
    {
    case token::category::authority:
        current_view = authority_reader.literal();
        input = input.substr(std::distance(input.begin(), authority_reader.tail().begin()));
        result = authority_reader.subcode();
        authority_reader.next();
        break;

    default:
        return authority_reader.subcode();
    }
    return result;
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_path()
{
    token::subcode::value result = token::subcode::end;
    switch (path_reader.category())
    {
    case token::category::path:
        current_view = path_reader.literal();
        input = input.substr(std::distance(input.begin(), path_reader.tail().begin()));
        result = path_reader.subcode();
        path_reader.next();
        break;

    default:
        return path_reader.subcode();
    }
    return result;
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_query()
{
    if (input.front() == syntax::character<value_type>::alpha_question_mark)
    {
        input.remove_prefix(1);
        std::size_t processed = syntax::query<value_type>::match(input);
        if (processed > 0)
        {
            current_view = input.substr(0, processed);
            input.remove_prefix(processed);
            return token::subcode::query;
        }
    }
    return token::subcode::end;
}

template <typename CharT>
token::subcode::value basic_url<CharT>::next_fragment()
{
    if (input.front() == syntax::character<value_type>::alpha_number_sign)
    {
        input.remove_prefix(1);
        std::size_t processed = syntax::fragment<value_type>::match(input);
        if (processed > 0)
        {
            current_view = input.substr(0, processed);
            input.remove_prefix(processed);
            return token::subcode::fragment;
        }
    }
    return token::subcode::end;
}

} // namespace reader
} // namespace url
} // namespace trial

#endif // TRIAL_URL_READER_URL_IPP
