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

#include <trial/url/reader/base.hpp>
#include <trial/url/reader/authority.hpp>
#include <trial/url/reader/path.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
class basic_url : public reader::base<CharT, basic_url>
{
    friend class reader::base<CharT, reader::basic_url>;
    typedef reader::base<CharT, reader::basic_url> super;

public:
    using typename super::value_type;
    using typename super::view_type;

    basic_url(const view_type&);

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

    token::subcode::value next_scheme();
    token::subcode::value next_hier_part();
    token::subcode::value next_authority();
    token::subcode::value next_path();
    token::subcode::value next_query();
    token::subcode::value next_fragment();

private:
    using super::input;
    using super::current_view;
    using super::current_token;

    url::reader::authority authority_reader;
    url::reader::path path_reader;
};

typedef basic_url<char> url;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/url.ipp>

#endif // TRIAL_URL_READER_URL_HPP
