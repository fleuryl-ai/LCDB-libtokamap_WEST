cmake_minimum_required( VERSION 3.15 )

project( west_data_source )

# Optional but recommended for shared libraries
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Specify C++ standard for all targets
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Extra cmake modules to find libraries
list(
    APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/cmake/Modules
)

find_package( LibTokaMap REQUIRED )

set( EXT_HEADERS
    src/ext_include/ctre/ctre.hpp
)

set( SOURCES
    src/west_data_source.cpp
    src/west_magnetics_handlers.cpp
    ${EXT_HEADERS}
)

add_subdirectory(src/west_data_access) 

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
    set( LIBRARY_NAME_SUFFIX "_debug" )
else()
    set( LIBRARY_NAME_SUFFIX "" )
endif()

set( LIBRARY_NAME "west_data_source${LIBRARY_NAME_SUFFIX}" )

add_library( ${LIBRARY_NAME} SHARED ${SOURCES} )

target_include_directories( ${LIBRARY_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ext_include
)

target_link_libraries( ${LIBRARY_NAME} PRIVATE
    LibTokaMap::libtokamap
    west_access
)

include( GNUInstallDirs )

install( TARGETS ${LIBRARY_NAME}
    EXPORT ${LIBRARY_NAME}Targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_executable( west_mapper
  src/west_mapper.cpp
)
target_link_libraries( west_mapper PRIVATE LibTokaMap::libtokamap ${LIBRARY_NAME} )