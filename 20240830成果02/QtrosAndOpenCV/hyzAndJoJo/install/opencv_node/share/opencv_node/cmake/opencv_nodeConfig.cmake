# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_opencv_node_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED opencv_node_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(opencv_node_FOUND FALSE)
  elseif(NOT opencv_node_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(opencv_node_FOUND FALSE)
  endif()
  return()
endif()
set(_opencv_node_CONFIG_INCLUDED TRUE)

# output package information
if(NOT opencv_node_FIND_QUIETLY)
  message(STATUS "Found opencv_node: 0.0.0 (${opencv_node_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'opencv_node' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${opencv_node_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(opencv_node_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${opencv_node_DIR}/${_extra}")
endforeach()
