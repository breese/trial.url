#ifndef TRIAL_URL_READER_QUERY_FORM_IPP
#define TRIAL_URL_READER_QUERY_FORM_IPP

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
#include <trial/url/syntax/pct_encoded.hpp>

namespace trial
{
namespace url
{
namespace reader
{

//-----------------------------------------------------------------------------
// detail::query_form_converter
//-----------------------------------------------------------------------------

namespace detail
{

template <typename CharT, typename ReturnType>
struct query_form_converter
{
    typedef typename basic_query_form<CharT>::value_type value_type;
    typedef typename basic_query_form<CharT>::view_type view_type;

    static ReturnType convert(const view_type& input)
    {
        ReturnType result;

        typename view_type::const_iterator end = input.end();
        for (typename view_type::const_iterator it = input.begin();
             it != end;
             ++it)
        {
            switch (*it)
            {
            case syntax::character<value_type>::alpha_plus:
                result += syntax::character<value_type>::alpha_space;
                break;

            case syntax::character<value_type>::alpha_percent:
                {
                    std::size_t processed = syntax::pct_encoded<value_type>::match(&*it);
                    if (processed == 0)
                        throw std::runtime_error("Incorrect percent encoding");
                    result += syntax::pct_encoded<value_type>::decode(&*it);
                    it += (processed - 1);
                }
                break;

            default:
                result += *it;
                break;
            }
        }
        return result;
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// query_form_reader
//-----------------------------------------------------------------------------

template <typename CharT>
basic_query_form<CharT>::basic_query_form(const view_type& input)
    : input(input)
{
    first();
}

template <typename CharT>
bool basic_query_form<CharT>::first()
{
    // Parse first key-value pair
    //
    // http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4.1
    //
    // form ::= ( form-list )?
    // form-list ::= form-key-value ( '&' form-key-value )*
    // form-key-value ::= text '=' text

    if (input.empty())
        return false;

    std::size_t processed = parse_key(input);
    if (processed == 0)
    {
        current_token = token::subcode::end;
        return false;
    }
    current_key = input.substr(0, processed);
    input.remove_prefix(processed);

    if (input.front() != syntax::character<value_type>::alpha_equal)
    {
        current_token = token::subcode::unknown;
        return false;
    }
    input.remove_prefix(1);
    current_token = token::subcode::query_form_key;

    processed = parse_value(input);
    if (processed == 0)
    {
        current_token = token::subcode::unknown;
        return false;
    }
    current_value = input.substr(0, processed);
    input.remove_prefix(processed);

    return true;
}

template <typename CharT>
bool basic_query_form<CharT>::next()
{
    if (input.empty())
    {
        current_token = token::subcode::end;
        return false;
    }

    // Skip list separator
    if (input.front() != syntax::character<value_type>::alpha_ampersand)
    {
        current_token = token::subcode::unknown;
        return false;
    }
    input.remove_prefix(1);
    return first();
}

template <typename CharT>
const typename basic_query_form<CharT>::view_type&
basic_query_form<CharT>::literal_key() const
{
    return current_key;
}

template <typename CharT>
const typename basic_query_form<CharT>::view_type&
basic_query_form<CharT>::literal_value() const
{
    return current_value;
}

template <typename CharT>
typename basic_query_form<CharT>::string_type
basic_query_form<CharT>::key() const
{
    return detail::query_form_converter<value_type, string_type>::convert(current_key);
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_query_form<CharT>::value() const
{
    return detail::query_form_converter<value_type, ReturnType>::convert(current_value);
}

template <typename CharT>
token::category::value basic_query_form<CharT>::category() const
{
    return token::category(code());
}

template <typename CharT>
token::code::value basic_query_form<CharT>::code() const
{
    return token::code(subcode());
}

template <typename CharT>
token::subcode::value basic_query_form<CharT>::subcode() const
{
    return current_token;
}

template <typename CharT>
std::size_t basic_query_form<CharT>::parse_key(const view_type& view)
{
    // All characters until =, &, or EOF

    typename view_type::const_iterator begin = view.begin();
    typename view_type::const_iterator end = view.end();
    typename view_type::const_iterator it = begin;
    for (;
         it != end;
         ++it)
    {
        if (*it == syntax::character<value_type>::alpha_equal)
            break;
        if (*it == syntax::character<value_type>::alpha_ampersand)
            break;
    }
    return std::distance(begin, it);
}

template <typename CharT>
std::size_t basic_query_form<CharT>::parse_value(const view_type& view)
{
    return parse_key(view);
}

} // namespace reader
} // namespace url
} // namespace trial

#endif // TRIAL_URL_READER_QUERY_FORM_IPP
