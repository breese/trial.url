#ifndef TRIAL_URL_TOKEN_HPP
#define TRIAL_URL_TOKEN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace url
{
namespace token
{

struct category
{
    enum value
    {
        error,
        scheme,
        authority,
        path,
        query,
        fragment
    };
};

struct code
{
    enum value
    {
        end,
        error,

        scheme,

        authority_userinfo,
        authority_host,
        authority_port,

        path_segment,

        query,

        fragment
    };
};

struct subcode
{
    enum value
    {
        end,
        unknown,

        scheme,

        authority_userinfo,
        authority_host_name,
        authority_host_ipv4,
        authority_host_ipv6,
        authority_port,

        path_segment,

        query,
        query_form_key,
        query_form_value,

        fragment
    };
};

inline category::value category(code::value value)
{
    switch (value)
    {
    case code::end:
        return category::error;

    case code::scheme:
        return category::scheme;

    case code::error:
        return category::error;

    case code::authority_userinfo:
    case code::authority_host:
    case code::authority_port:
        return category::authority;

    case code::path_segment:
        return category::path;

    case code::query:
        return category::query;

    case code::fragment:
        return category::fragment;
    }

    return category::error;
}

inline code::value code(subcode::value value)
{
    switch (value)
    {
    case subcode::end:
        return code::end;

    case subcode::unknown:
        return code::error;

    case subcode::scheme:
        return code::scheme;

    case subcode::authority_userinfo:
        return code::authority_userinfo;

    case subcode::authority_host_name:
    case subcode::authority_host_ipv4:
    case subcode::authority_host_ipv6:
        return code::authority_host;

    case subcode::authority_port:
        return code::authority_port;

    case subcode::path_segment:
        return code::path_segment;

    case subcode::query:
    case subcode::query_form_key:
    case subcode::query_form_value:
        return code::query;

    case subcode::fragment:
        return code::fragment;
    }

    return code::error;
}

inline category::value category(subcode::value value)
{
    return category(code(value));
}

} // namespace token
} // namespace url
} // namespace trial

#endif // TRIAL_URL_TOKEN_HPP
