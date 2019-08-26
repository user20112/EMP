# the hole script use CMake Version 3.1
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# define project name and required compiler flags
if(UNIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

# define project name and required compiler flags
project (GaAppBaseLib)

# set Application Name and build description
set (APPLICATIN_NAME ${PROJECT_NAME})
set (BUILD_DESCRIPTION "Basic Library for Gamma Applications")

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

# build config.h and add copy building informations to source
configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
)

# define List of source codes
set(SOURCES src/exceptions/ExceptionBase.cpp
            src/exceptions/ArgumentFaultException.cpp
            src/exceptions/LogicFaultException.cpp
            src/exceptions/SystemCallException.cpp
            src/ModuleInterface/LibContainer.cpp
            src/ModuleInterface/LibInstance.cpp
            src/ModuleInterface/ModuleInstance.cpp
            src/ModuleInterface/ModuleInterface.cpp
            src/network/NetworkHelper.cpp
            src/network/UDPConnection.cpp)
                   
# build an executable file
add_library(${PROJECT_NAME} SHARED
                            ${SOURCES}
                            ${CMAKE_CURRENT_BINARY_DIR}/LibVersionInfo.cpp)
                            
target_link_libraries(${PROJECT_NAME} ${BOOST_SYSTEM_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${BOOST_REGEX_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${BOOST_THREAD_LIBRARY})

                            
# add a version information to the project
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LibVersionInfo.cpp
                   COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildVersion.sh src/LibVersionInfo.template.cpp ${CMAKE_CURRENT_BINARY_DIR}/LibVersionInfo.cpp
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/LibVersionInfo.template.cpp
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET ${PROJECT_NAME}
                   PRE_BUILD
                   COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildVersion.sh src/LibVersionInfo.template.cpp ${CMAKE_CURRENT_BINARY_DIR}/LibVersionInfo.cpp
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/LibVersionInfo.template.cpp
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# build documentation
add_custom_target(doc${PROJECT_NAME}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/documentation
                  COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildDocumentation.sh ${CMAKE_CURRENT_SOURCE_DIR}/documentation/${PROJECT_NAME}.doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc ${CMAKE_INSTALL_PREFIX}/doc/${PROJECT_NAME}) 
add_dependencies(documentation doc${PROJECT_NAME})
 
# copy finished project file to install folder                   
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)
        
install(DIRECTORY include/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h")
         