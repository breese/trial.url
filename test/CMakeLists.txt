###############################################################################
# Trial.Url Test
###############################################################################

add_executable(test_url
  runner.cpp
  authority_parser_suite.cpp
  path_reader_suite.cpp
  query_form_reader_suite.cpp
)

target_link_libraries(test_url
  ${TRIAL_URL_DEPENDENT_LIBRARIES}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
