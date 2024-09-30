# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\head-unit_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\head-unit_autogen.dir\\ParseCache.txt"
  "head-unit_autogen"
  )
endif()
