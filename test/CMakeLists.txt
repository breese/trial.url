###############################################################################
# Trial.Url Test
###############################################################################

find_package(Boost 1.55.0 QUIET REQUIRED COMPONENTS
  unit_test_framework)

add_executable(test_url
  runner.cpp
  parser_suite.cpp
  reader/url_suite.cpp
  reader/authority_suite.cpp
  reader/path_suite.cpp
  reader/query_form_suite.cpp
  syntax/port_suite.cpp
  syntax/query_suite.cpp
)

target_link_libraries(test_url
  trial-url
  Boost::unit_test_framework)
