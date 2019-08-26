# the hole script use CMake Version 3.1
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# define project name and required compiler flags
if(UNIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

# define project name and required compiler flags
project (BeagleBoneResources)

# set Application Name and build description
set (APPLICATIN_NAME ${PROJECT_NAME})
set (BUILD_DESCRIPTION "Hardware resources for BeagleBone CPU")

# range for major version (inclusive): 1 .. 255
# range for minor version and patch (inclusive): 0 .. 4095
# range for tweak information (inclusive): 0 .. 4294967295
# when a version counter exceeds the specified limit, the internal version is not build correctly
# don't add leading 0 to the values!
set (PROJECT_VERSION_MAJOR   1)
set (PROJECT_VERSION_MINOR   0)
set (PROJECT_VERSION_PATCH   0)
set (PROJECT_VERSION_TWEAK   0)

#get additional liberaries
set (LIB_PRU_LOADER_PATH ./libs/pru_driver)
find_library(LIB_PRU_LOADER     prussdrv   ${LIB_PRU_LOADER_PATH}/lib )
find_library(LIB_PRU_LOADER_DBG prussdrvd  ${LIB_PRU_LOADER_PATH}/lib )

# additional include directories.
include_directories(AFTER 
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${LIB_PRU_LOADER_PATH}/include)

# build config.h and add copy building informations to source
configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
)

# define List of source codes
set(SOURCES src/pru/PruDriver.cpp
            src/pru/PruInterface.cpp)
                   
# build an executable file
add_library(${PROJECT_NAME} SHARED
                            ${SOURCES}
                            ${CMAKE_CURRENT_BINARY_DIR}/LibVersionInfo.cpp)

target_link_libraries(${PROJECT_NAME} GaAppBaseLib)

if(DEBUG)
target_link_libraries(${PROJECT_NAME} ${LIB_PRU_LOADER_DBG})
else (DBEUG)
target_link_libraries(${PROJECT_NAME} ${LIB_PRU_LOADER})
endif(DEBUG)
                            
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
         