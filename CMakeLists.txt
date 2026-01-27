cmake_minimum_required(VERSION 3.16)
project(Cleaver2 LANGUAGES CXX)

# Collect all sources under src/lib/cleaver2
file(GLOB_RECURSE CLEAVER2_SOURCES
  src/lib/cleaver2/*.cpp
  src/lib/cleaver2/*.cxx
  src/lib/cleaver2/*.cc
)

file(GLOB_RECURSE CLEAVER2_HEADERS
  src/lib/cleaver2/*.h
  src/lib/cleaver2/*.hpp
)

# Build the library
add_library(cleaver2 ${CLEAVER2_SOURCES})

# Public include path
target_include_directories(cleaver2 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/cleaver2
)

# Ensure PIC for static builds
set_target_properties(cleaver2 PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Install headers into <INSTALL_DIR>/include/cleaver2
install(FILES ${CLEAVER2_HEADERS} DESTINATION include/cleaver2)

# Install library into <INSTALL_DIR>/lib
install(TARGETS cleaver2
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
