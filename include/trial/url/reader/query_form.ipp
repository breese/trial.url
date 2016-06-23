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
// converter
//-----------------------------------------------------------------------------

namespace detail
{

template <typename CharT,
          typename ReturnType>
struct converter<CharT,
                 basic_query_form,
                 ReturnType,
                 typename boost::enable_if< boost::is_same<ReturnType, std::basic_string<CharT> > >::type>
{
    typedef typename base<CharT, basic_query_form>::view_type view_type;
    static ReturnType convert(const view_type& view)
    {
        ReturnType result;

        typename view_type::const_iterator end = view.end();
        for (typename view_type::const_iterator it = view.begin();
             it != end;
             ++it)
        {
            switch (*it)
            {
            case syntax::character<CharT>::alpha_plus:
                result += syntax::character<CharT>::alpha_space;
                break;

            case syntax::character<CharT>::alpha_percent:
                {
                    std::size_t processed = syntax::pct_encoded<CharT>::match(&*it);
                    if (processed == 0)
                        throw std::runtime_error("Incorrect percent encoding");
                    result += syntax::pct_encoded<CharT>::decode(&*it);
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
    : super(input),
      is_key(true)
{
    first();
}

template <typename CharT>
void basic_query_form<CharT>::do_reset()
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

    is_key = true;
    return next();
}

template <typename CharT>
bool basic_query_form<CharT>::do_next()
{
    // Allow empty value field
    if (input.empty() && is_key)
    {
        current_token = token::subcode::end;
        return false;
    }

    if (is_key)
    {
        next_key();
        is_key = (subcode() == token::subcode::end);
    }
    else
    {
        next_value();
        is_key = true;
    }
    return category() != token::category::error;
}

template <typename CharT>
void basic_query_form<CharT>::next_key()
{
    std::size_t processed = parse_key(input);
    if (processed == 0)
    {
        current_token = token::subcode::end;
        return;
    }
    current_view = input.substr(0, processed);
    input.remove_prefix(processed);

    if (input.front() != syntax::character<value_type>::alpha_equal)
    {
        current_token = token::subcode::unknown;
        return;
    }
    input.remove_prefix(1);
    current_token = token::subcode::query_form_key;
}

template <typename CharT>
void basic_query_form<CharT>::next_value()
{
    std::size_t processed = parse_value(input);
    current_view = input.substr(0, processed);
    input.remove_prefix(processed);

    // Skip list separator
    if (input.empty())
    {
        // Ignore end
    }
    else if (input.front() == syntax::character<value_type>::alpha_ampersand)
    {
        input.remove_prefix(1);
    }
    current_token = token::subcode::query_form_value;
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
