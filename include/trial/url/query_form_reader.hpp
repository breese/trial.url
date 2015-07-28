#ifndef TRIAL_URL_QUERY_FORM_READER_HPP
#define TRIAL_URL_QUERY_FORM_READER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/utility/string_ref.hpp>
#include <trial/url/token.hpp>

// http://www.w3.org/TR/html401/interact/forms.html

namespace trial
{
namespace url
{

template <typename CharT>
class basic_query_form_reader
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;
    typedef std::basic_string<value_type> string_type;

    basic_query_form_reader(const view_type&);

    bool next();

    token::category::value category() const;
    token::code::value code() const;
    token::subcode::value subcode() const;

    const view_type& literal_key() const;
    const view_type& literal_value() const;

    string_type key() const;
    template <typename ReturnType> ReturnType value() const;

private:
    bool first();
    std::size_t parse_key(const view_type&);
    std::size_t parse_value(const view_type&);

private:
    view_type input;
    token::subcode::value current_token;
    view_type current_key;
    view_type current_value;
};

typedef basic_query_form_reader<char> query_form_reader;

} // namespace url
} // namespace trial

#include <trial/url/query_form_reader.ipp>

#endif // TRIAL_URL_QUERY_FORM_READER_HPP
