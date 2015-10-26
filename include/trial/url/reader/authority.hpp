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
#include <trial/url/reader/base.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
class basic_authority : public reader::base<CharT, basic_authority>
{
    friend class reader::base<CharT, reader::basic_authority>;
    typedef reader::base<CharT, reader::basic_authority> super;

public:
    using typename super::value_type;
    using typename super::view_type;

    basic_authority(const view_type&);

    using super::next;
    using super::reset;
    using super::category;
    using super::code;
    using super::subcode;
    using super::literal;
    using super::value;
    using super::tail;

private:
    void first();
    void do_reset();
    bool do_next();

    token::subcode::value next_userinfo();
    token::subcode::value next_host();
    token::subcode::value next_port();

private:
    using super::input;
    using super::current_view;
    using super::current_token;
};

typedef basic_authority<char> authority;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/authority.ipp>

#endif // TRIAL_URL_READER_AUTHORITY_HPP
