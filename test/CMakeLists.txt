###############################################################################
# Trial.Url Test
###############################################################################

add_executable(test_url
  runner.cpp
  parser_suite.cpp
  reader/url_suite.cpp
  reader/authority_suite.cpp
  reader/path_suite.cpp
  reader/query_form_suite.cpp
  syntax/query_suite.cpp
)

target_link_libraries(test_url
  ${TRIAL_URL_DEPENDENT_LIBRARIES}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
