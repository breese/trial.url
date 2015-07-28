#ifndef TRIAL_URL_READER_BASE_IPP
#define TRIAL_URL_READER_BASE_IPP

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
namespace reader
{

//-----------------------------------------------------------------------------
// converter
//-----------------------------------------------------------------------------

namespace detail
{

template <typename CharT,
          template <typename> class ReaderType,
          typename ReturnType,
          typename Enable = void>
struct converter
{
    typedef typename base<CharT, ReaderType>::view_type view_type;
    static ReturnType convert(const view_type&);
};

template <typename CharT,
          template <typename> class ReaderType,
          typename ReturnType>
struct converter<CharT,
                 ReaderType,
                 ReturnType,
                 typename boost::enable_if< boost::is_same<ReturnType, std::basic_string<CharT> > >::type>
{
    typedef typename base<CharT, ReaderType>::view_type view_type;
    static ReturnType convert(const view_type& view)
    {
        return ReturnType(view.begin(), view.end());
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// base
//-----------------------------------------------------------------------------

template <typename CharT, template <typename> class ReaderType>
base<CharT, ReaderType>::base(const view_type& input)
    : input(input),
      current_view(input),
      current_token(token::subcode::end)
{
}

template <typename CharT, template <typename> class ReaderType>
bool base<CharT, ReaderType>::next()
{
    return self().do_next();
}

template <typename CharT, template <typename> class ReaderType>
void base<CharT, ReaderType>::reset(const view_type& view)
{
    input = current_view = view;
    current_token = token::subcode::end;
    self().do_reset();
}

template <typename CharT, template <typename> class ReaderType>
token::category::value base<CharT, ReaderType>::category() const
{
    return token::category(subcode());
}

template <typename CharT, template <typename> class ReaderType>
token::code::value base<CharT, ReaderType>::code() const
{
    return token::code(subcode());
}

template <typename CharT, template <typename> class ReaderType>
token::subcode::value base<CharT, ReaderType>::subcode() const
{
    return current_token;
}

template <typename CharT, template <typename> class ReaderType>
const typename base<CharT, ReaderType>::view_type&
base<CharT, ReaderType>::literal() const
{
    return current_view;
}

template <typename CharT, template <typename> class ReaderType>
template <typename ReturnType>
ReturnType base<CharT, ReaderType>::value() const
{
    return detail::converter<CharT, ReaderType, ReturnType>::convert(current_view);
}

template <typename CharT, template <typename> class ReaderType>
const typename base<CharT, ReaderType>::view_type&
base<CharT, ReaderType>::tail() const
{
    return input;
}

template <typename CharT, template <typename> class ReaderType>
ReaderType<CharT>& base<CharT, ReaderType>::self()
{
    return *static_cast<ReaderType<CharT>*>(this);
}

} // namespace reader
} // namespace url
} // namespace trial

#endif // TRIAL_URL_READER_BASE_IPP
