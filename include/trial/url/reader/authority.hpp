#ifndef TRIAL_URL_READER_AUTHORITY_HPP
#define TRIAL_URL_READER_AUTHORITY_HPP

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
namespace reader
{

template <typename CharT>
class basic_authority
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    basic_authority(const view_type&);

    void reset(const view_type&);

    bool next();

    token::category::value category() const;
    token::code::value code() const;
    token::subcode::value subcode() const;

    const view_type& literal() const;
    template <typename ReturnType> ReturnType value() const;

    const view_type& tail() const;

private:
    void first();

    token::subcode::value next_userinfo();
    token::subcode::value next_host();
    token::subcode::value next_port();

private:
    view_type input;
    token::subcode::value current_token;
    view_type current_view;
};

typedef basic_authority<char> authority;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/authority.ipp>

#endif // TRIAL_URL_READER_AUTHORITY_HPP
