###############################################################################
#
# Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.1)
project(trial.uri)

set(TRIAL_URL_STANDALONE ON CACHE BOOL "Build as standalone")

set(TRIAL_URL_BUILD_DIR ${CMAKE_BINARY_DIR})
set(TRIAL_URL_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_URL_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_URL_BUILD_DIR}/bin)

if (MSVC)
  set(TRIAL_URL_WARNING_FLAGS /W3)
else()
  set(TRIAL_URL_WARNING_FLAGS -Wall -Wextra -pedantic -Werror=return-type)
endif()

###############################################################################
# Boost package
###############################################################################

find_package(Boost 1.55.0 QUIET REQUIRED)

###############################################################################
# Trial.Url package
###############################################################################

add_definitions(${TRIAL_URL_WARNING_FLAGS})

add_library(trial-url INTERFACE)
target_include_directories(trial-url INTERFACE
  "${TRIAL_URL_ROOT}/include"
  "${Boost_INCLUDE_DIR}")

if (TRIAL_URL_STANDALONE)
  add_subdirectory(test)
endif()
