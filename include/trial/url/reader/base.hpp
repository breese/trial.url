#ifndef TRIAL_URL_READER_BASE_HPP
#define TRIAL_URL_READER_BASE_HPP

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
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <trial/url/token.hpp>

namespace trial
{
namespace url
{
namespace reader
{

template <typename CharT, template <typename> class ReaderType>
class base
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    base(const view_type&);

    bool next();
    void reset(const view_type&);

    token::category::value category() const;
    token::code::value code() const;
    token::subcode::value subcode() const;

    const view_type& literal() const;
    template <typename ReturnType> ReturnType value() const;
    const view_type& tail() const;

private:
    ReaderType<value_type>& self();

protected:
    view_type input;
    view_type current_view;
    token::subcode::value current_token;
};

} // namespace reader
} // namespace url
} // namespace trial

#include <trial/url/reader/base.ipp>

#endif // TRIAL_URL_READER_BASE_HPP
