#ifndef TRIAL_URL_READER_QUERY_FORM_HPP
#define TRIAL_URL_READER_QUERY_FORM_HPP

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
#include <trial/url/reader/base.hpp>
#include <trial/url/token.hpp>

// http://www.w3.org/TR/html401/interact/forms.html

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT>
class basic_query_form : public reader::base<CharT, basic_query_form>
{
    friend class reader::base<CharT, reader::basic_query_form>;
    typedef reader::base<CharT, reader::basic_query_form> super;

public:
    using typename super::value_type;
    using typename super::view_type;

    basic_query_form(const view_type&);

    using super::next;
    using super::reset;
    using super::category;
    using super::code;
    using super::subcode;
    using super::literal;
    using super::value;

private:
    bool first();
    void do_reset();
    bool do_next();
    void next_key();
    void next_value();
    std::size_t parse_key(const view_type&);
    std::size_t parse_value(const view_type&);

private:
    using super::input;
    using super::current_view;
    using super::current_token;

    bool is_key;
};

typedef basic_query_form<char> query_form;

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/query_form.ipp>

#endif // TRIAL_URL_READER_QUERY_FORM_HPP
