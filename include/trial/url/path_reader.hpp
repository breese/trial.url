#ifndef TRIAL_URL_PATH_READER_HPP
#define TRIAL_URL_PATH_READER_HPP

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
#include <boost/utility/string_ref.hpp>
#include <trial/url/token.hpp>

namespace trial
{
namespace url
{

template <typename CharT>
class basic_path_reader
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    basic_path_reader(const view_type&);

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
    token::subcode::value next_done();
    token::subcode::value next_abempty();

private:
    view_type input;
    typedef token::subcode::value (basic_path_reader::*next_function)();
    next_function next_state;
    token::subcode::value current_token;
    view_type current_view;
};

typedef basic_path_reader<char> path_reader;

} // namespace url
} // namespace trial

#include <trial/url/path_reader.ipp>

#endif // TRIAL_URL_PATH_READER_HPP
