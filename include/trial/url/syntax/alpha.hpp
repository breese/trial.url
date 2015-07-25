#ifndef TRIAL_URL_SYNTAX_ALPHA_HPP
#define TRIAL_URL_SYNTAX_ALPHA_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/url/syntax/character.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
class alpha
{
public:
    typedef CharT value_type;

    static std::size_t match(value_type);
};

} // namespace syntax
} // namespace url
} // namespace trial

#include <trial/url/syntax/alpha.ipp>

#endif // TRIAL_URL_SYNTAX_ALPHA_HPP
