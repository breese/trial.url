#ifndef TRIAL_URL_AUTHORITY_READER_HPP
#define TRIAL_URL_AUTHORITY_READER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/utility/string_ref.hpp>
#include <trial/url/token.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
class basic_authority_reader
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    basic_authority_reader(const view_type&);

    bool next();

    token::category::value category() const;
    token::code::value code() const;
    token::subcode::value subcode() const;

    const view_type& literal() const;
    template <typename ReturnType> ReturnType value() const;

private:
    void first();

    token::subcode::value next_userinfo();
    token::subcode::value next_host();
    token::subcode::value next_port();

private:
    view_type input;
    token::subcode::value current_type;
    view_type current_view;
};

typedef basic_authority_reader<char> authority_reader;

} // namespace url
} // namespace trial

#include <trial/url/authority_reader.ipp>

#endif // TRIAL_URL_AUTHORITY_READER_HPP
