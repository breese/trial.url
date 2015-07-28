#ifndef TRIAL_URL_READER_PATH_HPP
#define TRIAL_URL_READER_PATH_HPP

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
#include <boost/config.hpp>
#include <trial/url/reader/base.hpp>
#include <trial/url/token.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
class basic_path : public reader::base<CharT, basic_path>
{
    friend class reader::base<CharT, basic_path>;
    typedef reader::base<CharT, basic_path> super;

public:
    using typename super::value_type;
    using typename super::view_type;

    basic_path(const view_type&);

    using super::next;
    using super::reset;
    using super::category;
    using super::code;
    using super::subcode;
    using super::literal;
    using super::value;

private:
    void first();
    void do_reset();
    bool do_next();
    token::subcode::value next_done();
    token::subcode::value next_abempty();

private:
    using super::input;
    using super::current_view;
    using super::current_token;

    typedef token::subcode::value (basic_path::*next_function)();
    next_function next_state;
};

typedef basic_path<char> path;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/path.ipp>

#endif // TRIAL_URL_READER_PATH_HPP
