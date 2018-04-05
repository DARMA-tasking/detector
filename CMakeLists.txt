cmake_minimum_required(VERSION 3.8)
project(detection)

set(CMAKE_CXX_STANDARD 14)

enable_language(CXX)

include (CTest)
enable_testing()

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)
#set(PROJECT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

file(
  GLOB
  HEADER_FILES
  ${PROJECT_SOURCE_DIR}/*.h
)

set(DETECTION_LIBRARY detection)

install(FILES ${HEADER_FILES} DESTINATION include)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_EXAMPLE_DIR})

macro(add_test_for_example test_name test_exec)
  add_test(
    ${test_name} ${test_exec} ${ARGN}
  )

  set_tests_properties(
    ${test_name}
    PROPERTIES TIMEOUT 300 FAIL_REGULAR_EXPRESSION "FAILED;WARNING"
  )
endmacro()

file(
  GLOB
  PROJECT_EXAMPLES
  RELATIVE
  "${PROJECT_EXAMPLE_DIR}"
  "${PROJECT_EXAMPLE_DIR}/*.cc"
)

#message("examples= ${PROJECT_EXAMPLES}")

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

  add_test_for_example(
    ${EXAMPLE}
    ${CMAKE_CURRENT_BINARY_DIR}/${EXAMPLE}
  )

endforeach()

add_library(darma_detector INTERFACE)
target_include_directories(darma_detector INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS darma_detector EXPORT darma_detector)
install(EXPORT darma_detector DESTINATION cmake)

configure_file(
  cmake/darma_detectorConfig.cmake.in
  "${PROJECT_BINARY_DIR}/darma_detectorConfig.cmake" @ONLY
)
install(
  FILES
  "${PROJECT_BINARY_DIR}/darma_detectorConfig.cmake" 
  DESTINATION cmake 
)

