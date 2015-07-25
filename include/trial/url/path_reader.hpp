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
    typedef std::basic_string<value_type> string_type;

    basic_path_reader(const view_type&);

    bool next();

    const view_type& literal_segment() const;
    string_type segment() const;

private:
    void first();
    bool next_done();
    bool next_abempty();

private:
    view_type input;
    typedef bool (basic_path_reader::*next_function)();
    next_function next_state;
    view_type current_segment;
};

typedef basic_path_reader<char> path_reader;

} // namespace url
} // namespace trial

#include <trial/url/path_reader.ipp>

#endif // TRIAL_URL_PATH_READER_HPP
