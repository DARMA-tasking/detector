
macro(add_test_for_example test_name test_exec)
  add_test(${test_name} ${test_exec} ${ARGN})

  set_tests_properties(
    ${test_name}
    PROPERTIES TIMEOUT 300 FAIL_REGULAR_EXPRESSION "FAILED;WARNING"
  )
endmacro()

set(PROJECT_EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(
  GLOB
  PROJECT_EXAMPLES
  RELATIVE
  "${PROJECT_EXAMPLE_DIR}"
  "${PROJECT_EXAMPLE_DIR}/*.cc"
)

foreach(EXAMPLE_FULL ${PROJECT_EXAMPLES})
  GET_FILENAME_COMPONENT(
    EXAMPLE
    ${EXAMPLE_FULL}
    NAME_WE
  )

  add_executable(
    ${EXAMPLE}
    ${PROJECT_EXAMPLE_DIR}/${EXAMPLE}.cc
  )

  add_dependencies(detector_examples ${EXAMPLE})

  target_link_libraries(${EXAMPLE} ${DETECTION_LIBRARY})

  add_test_for_example(
    ${EXAMPLE}
    ${CMAKE_CURRENT_BINARY_DIR}/${EXAMPLE}
  )
endforeach()
