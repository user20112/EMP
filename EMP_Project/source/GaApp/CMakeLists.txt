# the hole script use CMake Version 3.1
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# define project name and required compiler flags
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

# define project name and required compiler flags
project (GaApp)

# set Application Name and build description
set (APPLICATIN_NAME ${PROJECT_NAME})
set (BUILD_DESCRIPTION "Testing Project for BaseTecDriver-Development")

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
                    ./include
                    ${PROJECT_BINARY_DIR}
                    ${PHAO_INCLUDES})

# build config.h and add copy building informations to source
configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
)

# define List of source codes
set(SOURCES src/main.cpp
            src/AppConfig.cpp)
                   
# build an executable file
add_executable(${PROJECT_NAME} ${SOURCES}
                               ${CMAKE_CURRENT_BINARY_DIR}/AppVersionInfo.cpp)

target_link_libraries(${PROJECT_NAME} PugiXML)
target_link_libraries(${PROJECT_NAME} GaAppBaseLib)
target_link_libraries(${PROJECT_NAME} GaGCppAPI)
target_link_libraries(${PROJECT_NAME} ${PHAO_MQT_3A})
target_link_libraries(${PROJECT_NAME} ${PHAO_MQT_3C})


# add a version information to the project
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/AppVersionInfo.cpp
                   COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildVersion.sh src/AppVersionInfo.template.cpp ${CMAKE_CURRENT_BINARY_DIR}/AppVersionInfo.cpp
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/AppVersionInfo.template.cpp
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
 
add_custom_command(TARGET ${PROJECT_NAME}
                   PRE_BUILD
                   COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildVersion.sh src/AppVersionInfo.template.cpp ${CMAKE_CURRENT_BINARY_DIR}/AppVersionInfo.cpp
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/AppVersionInfo.template.cpp
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# build documentation
add_custom_target(doc${PROJECT_NAME}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/documentation
                  COMMAND sh  /cygdrive/${ROOT_DRIVE}/Scripts/buildDocumentation.sh ${CMAKE_CURRENT_SOURCE_DIR}/documentation/${PROJECT_NAME}.doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc ${CMAKE_INSTALL_PREFIX}/doc/${PROJECT_NAME}) 
add_dependencies(documentation doc${PROJECT_NAME})
 
# copy finished project file to install folder                   
install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)
        
install(FILES run.sh
        DESTINATION .)
        
install(DIRECTORY config/
        DESTINATION config
        FILES_MATCHING REGEX "(.+\.xml$)|(.+\.conf$)")
        
install(DIRECTORY service/
        DESTINATION service)
        