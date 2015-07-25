#ifndef TRIAL_URL_SYNTAX_CHARACTER_HPP
#define TRIAL_URL_SYNTAX_CHARACTER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config.hpp>

namespace trial
{
namespace url
{
namespace syntax
{

//-----------------------------------------------------------------------------
// character
//-----------------------------------------------------------------------------

template <typename CharT>
class character
{
};

//-----------------------------------------------------------------------------
// char specialization
//-----------------------------------------------------------------------------

template <>
class character<char>
{
public:
    typedef char value_type;

    BOOST_STATIC_CONSTANT(value_type, alpha_space = ' ');
    BOOST_STATIC_CONSTANT(value_type, alpha_exclamation = '!');
    BOOST_STATIC_CONSTANT(value_type, alpha_number_sign = '#');
    BOOST_STATIC_CONSTANT(value_type, alpha_dollar = '$');
    BOOST_STATIC_CONSTANT(value_type, alpha_percent = '%');
    BOOST_STATIC_CONSTANT(value_type, alpha_ampersand = '&');
    BOOST_STATIC_CONSTANT(value_type, alpha_apostrophe = '\'');
    BOOST_STATIC_CONSTANT(value_type, alpha_parens_open = '(');
    BOOST_STATIC_CONSTANT(value_type, alpha_parens_close = ')');
    BOOST_STATIC_CONSTANT(value_type, alpha_asterisk = '*');
    BOOST_STATIC_CONSTANT(value_type, alpha_plus = '+');
    BOOST_STATIC_CONSTANT(value_type, alpha_comma = ',');
    BOOST_STATIC_CONSTANT(value_type, alpha_minus = '-');
    BOOST_STATIC_CONSTANT(value_type, alpha_dot = '.');
    BOOST_STATIC_CONSTANT(value_type, alpha_slash = '/');
    BOOST_STATIC_CONSTANT(value_type, alpha_0 = '0');
    BOOST_STATIC_CONSTANT(value_type, alpha_1 = '1');
    BOOST_STATIC_CONSTANT(value_type, alpha_2 = '2');
    BOOST_STATIC_CONSTANT(value_type, alpha_3 = '3');
    BOOST_STATIC_CONSTANT(value_type, alpha_4 = '4');
    BOOST_STATIC_CONSTANT(value_type, alpha_5 = '5');
    BOOST_STATIC_CONSTANT(value_type, alpha_6 = '6');
    BOOST_STATIC_CONSTANT(value_type, alpha_7 = '7');
    BOOST_STATIC_CONSTANT(value_type, alpha_8 = '8');
    BOOST_STATIC_CONSTANT(value_type, alpha_9 = '9');
    BOOST_STATIC_CONSTANT(value_type, alpha_colon = ':');
    BOOST_STATIC_CONSTANT(value_type, alpha_semicolon = ';');
    BOOST_STATIC_CONSTANT(value_type, alpha_equal = '=');
    BOOST_STATIC_CONSTANT(value_type, alpha_question_mark = '?');
    BOOST_STATIC_CONSTANT(value_type, alpha_at = '@');
    BOOST_STATIC_CONSTANT(value_type, alpha_A = 'A');
    BOOST_STATIC_CONSTANT(value_type, alpha_B = 'B');
    BOOST_STATIC_CONSTANT(value_type, alpha_C = 'C');
    BOOST_STATIC_CONSTANT(value_type, alpha_D = 'D');
    BOOST_STATIC_CONSTANT(value_type, alpha_E = 'E');
    BOOST_STATIC_CONSTANT(value_type, alpha_F = 'F');
    BOOST_STATIC_CONSTANT(value_type, alpha_Z = 'Z');
    BOOST_STATIC_CONSTANT(value_type, alpha_a = 'a');
    BOOST_STATIC_CONSTANT(value_type, alpha_b = 'b');
    BOOST_STATIC_CONSTANT(value_type, alpha_c = 'c');
    BOOST_STATIC_CONSTANT(value_type, alpha_d = 'd');
    BOOST_STATIC_CONSTANT(value_type, alpha_e = 'e');
    BOOST_STATIC_CONSTANT(value_type, alpha_f = 'f');
    BOOST_STATIC_CONSTANT(value_type, alpha_z = 'z');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_open = '[');
    BOOST_STATIC_CONSTANT(value_type, alpha_bracket_close = ']');
    BOOST_STATIC_CONSTANT(value_type, alpha_underscore = '_');
    BOOST_STATIC_CONSTANT(value_type, alpha_tilde = '~');
};

} // namespace syntax
} // namespace url
} // namespace trial

#endif // TRIAL_URL_SYNTAX_CHARACTER_HPP
