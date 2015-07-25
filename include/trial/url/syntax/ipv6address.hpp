#ifndef TRIAL_URL_SYNTAX_IPV6ADDRESS_HPP
#define TRIAL_URL_SYNTAX_IPV6ADDRESS_HPP

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

namespace trial
{
namespace url
{
namespace syntax
{

template <typename CharT>
class ipv6address
{
public:
    typedef CharT value_type;
    typedef boost::basic_string_ref<value_type> view_type;

    static std::size_t match(const view_type&);

private:
    static std::size_t match_alternative_1(const view_type&);
    static std::size_t match_alternative_2(const view_type&);
    static std::size_t match_alternative_3(const view_type&, std::size_t, std::size_t);
    static std::size_t match_alternative_4(const view_type&);
    static std::size_t match_alternative_5(const view_type&);
    static std::size_t match_h16(const view_type&);
    static std::size_t match_ls32(const view_type&);
};

} // namespace syntax
} // namespace url
} // namespace trial

#include <trial/url/syntax/ipv6address.ipp>

#endif // TRIAL_URL_SYNTAX_IPV6ADDRESS_HPP
