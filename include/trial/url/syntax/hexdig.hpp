#ifndef TRIAL_URL_SYNTAX_HEXDIG_HPP
#define TRIAL_URL_SYNTAX_HEXDIG_HPP

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
#include <trial/url/syntax/character.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
class hexdig
{
public:
    typedef CharT value_type;
    typedef typename std::char_traits<value_type>::int_type int_type;

    static std::size_t match(value_type);
    static int_type decode(value_type);
};

} // namespace syntax
} // namespace url
} // namespace trial

#include <trial/url/syntax/hexdig.ipp>

#endif // TRIAL_URL_SYNTAX_HEXDIG_HPP
