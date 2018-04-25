cmake_minimum_required(VERSION 3.8)
project(detection)

file(
  GLOB
  HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(DETECTION_LIBRARY darma_detector)

add_custom_target(detector_examples)
add_subdirectory(examples)

install(FILES ${HEADER_FILES} DESTINATION include)

add_library(${DETECTION_LIBRARY} INTERFACE)

target_compile_features(${DETECTION_LIBRARY} INTERFACE cxx_std_14)

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
  NAMESPACE               darma::backend::
  FILE                    "darma_detectorTargets.cmake"
)

configure_file(
  cmake/darma_detectorConfig.cmake.in
  "${PROJECT_BINARY_DIR}/darma_detectorConfig.cmake" @ONLY
)

install(
  FILES "${PROJECT_BINARY_DIR}/darma_detectorConfig.cmake"
  DESTINATION cmake
)

export(
  TARGETS                   ${DETECTION_LIBRARY}
  FILE                      "darma_detectionTargets.cmake"
  NAMESPACE                 darma::backend::
)
