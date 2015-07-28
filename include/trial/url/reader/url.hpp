#ifndef TRIAL_URL_READER_URL_HPP
#define TRIAL_URL_READER_URL_HPP

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
#include <trial/url/reader/authority.hpp>
#include <trial/url/reader/path.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
class basic_url
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    basic_url(const view_type&);

    bool next();

    token::category::value category() const;
    token::code::value code() const;
    token::subcode::value subcode() const;

    const view_type& literal() const;
    template <typename ReturnType> ReturnType value() const;

private:
    void first();

    token::subcode::value next_scheme();
    token::subcode::value next_hier_part();
    token::subcode::value next_authority();
    token::subcode::value next_path();
    token::subcode::value next_query();
    token::subcode::value next_fragment();

private:
    view_type input;
    token::subcode::value current_token;
    view_type current_view;
    url::reader::authority authority_reader;
    url::reader::path path_reader;
};

typedef basic_url<char> url;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/url.ipp>

#endif // TRIAL_URL_READER_URL_HPP
