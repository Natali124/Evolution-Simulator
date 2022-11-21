# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Evolution_Simulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Evolution_Simulator_autogen.dir/ParseCache.txt"
  "Evolution_Simulator_autogen"
  )
endif()
