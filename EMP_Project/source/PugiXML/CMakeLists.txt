# the hole script use CMake Version 3.1
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# define project name and required compiler flags
if(UNIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

# define project name and required compiler flags
project (PugiXML)

# set Application Name and build description
set (APPLICATIN_NAME ${PROJECT_NAME})
set (BUILD_DESCRIPTION "develop build")

# range for major version (inclusive): 1 .. 255
# range for minor version and patch (inclusive): 0 .. 4095
# range for tweak information (inclusive): 0 .. 4294967295
# when a version counter exceeds the specified limit, the internal version is not build correctly
# don't add leading 0 to the values!
set (PROJECT_VERSION_MAJOR   1)
set (PROJECT_VERSION_MINOR   0)
set (PROJECT_VERSION_PATCH   0)
set (PROJECT_VERSION_TWEAK   0)

# additional include directories.
include_directories(AFTER
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_BINARY_DIR})

# define List of source codes
set(SOURCES src/pugixml.cpp)
                   
# build an executable file
add_library(${PROJECT_NAME} SHARED
                            ${SOURCES})
 
# copy documentation
install(DIRECTORY docs/
        DESTINATION doc/${PROJECT_NAME})
  
# copy finished project file to install folder                   
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)
         
install(DIRECTORY src/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h")
        