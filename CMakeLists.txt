cmake_minimum_required(VERSION 3.8)
project(detector)

include(cmake/turn_on_warnings.cmake)

# Try to find ccache to speed up compilation
find_program(ccache_binary ccache)
if (ccache_binary)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${ccache_binary}")
endif()

file(
  GLOB
  HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(DETECTOR_LIBRARY detector)
set(DETECTOR_LIBRARY_NS vt::lib::detector)

add_custom_target(detector_examples)
add_subdirectory(examples)

install(FILES ${HEADER_FILES} DESTINATION include)

add_library(${DETECTOR_LIBRARY} INTERFACE)
add_library(${DETECTOR_LIBRARY_NS} ALIAS ${DETECTOR_LIBRARY})

target_compile_features(${DETECTOR_LIBRARY} INTERFACE cxx_std_14)
target_compile_features(
  ${DETECTOR_LIBRARY} INTERFACE
  cxx_variadic_templates
  cxx_auto_type
  cxx_constexpr
)

target_include_directories(
  ${DETECTOR_LIBRARY} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

install(
  TARGETS                 ${DETECTOR_LIBRARY}
  EXPORT                  ${DETECTOR_LIBRARY}
  LIBRARY DESTINATION     lib
  ARCHIVE DESTINATION     lib
  RUNTIME DESTINATION     bin
  INCLUDES DESTINATION    include
)

install(
  EXPORT                  ${DETECTOR_LIBRARY}
  DESTINATION             cmake
  NAMESPACE               vt::lib::
  FILE                    "detectorTargets.cmake"
  COMPONENT               runtime
)

configure_file(
  cmake/detectorConfig.cmake.in
  "${PROJECT_BINARY_DIR}/detectorConfig.cmake" @ONLY
)

install(
  FILES "${PROJECT_BINARY_DIR}/detectorConfig.cmake"
  DESTINATION cmake
)

export(
  TARGETS                   ${DETECTOR_LIBRARY}
  FILE                      "detectorTargets.cmake"
  NAMESPACE                 vt::lib::
)
