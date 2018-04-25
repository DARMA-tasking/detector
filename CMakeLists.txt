cmake_minimum_required(VERSION 3.8)
project(detection)

file(
  GLOB
  HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(DETECTION_LIBRARY detector)
set(DETECTION_LIBRARY_NS ::vt::lib::detector)

add_custom_target(detector_examples)
add_subdirectory(examples)

install(FILES ${HEADER_FILES} DESTINATION include)

add_library(${DETECTION_LIBRARY} INTERFACE)
add_library(${DETECTION_LIBRARY_NS} ALIAS ${DETECTION_LIBRARY})

target_compile_features(${DETECTION_LIBRARY} INTERFACE cxx_std_14)
target_compile_features(
  ${DETECTION_LIBRARY} INTERFACE
  cxx_variadic_templates
  cxx_auto_type
  cxx_constexpr
)

target_include_directories(
  ${DETECTION_LIBRARY} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

install(
  TARGETS                 ${DETECTION_LIBRARY}
  EXPORT                  ${DETECTION_LIBRARY}
  LIBRARY DESTINATION     lib
  ARCHIVE DESTINATION     lib
  RUNTIME DESTINATION     bin
  INCLUDES DESTINATION    include
)

install(
  EXPORT                  ${DETECTION_LIBRARY}
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
  TARGETS                   ${DETECTION_LIBRARY}
  FILE                      "detectionTargets.cmake"
  NAMESPACE                 vt::lib::
)
