# Install script for directory: C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/source/BaseTecDriver

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/Install/Linux-arm/Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/BaseTecDriver/CMakeFiles/CMakeRelink.dir/libBaseTecDriver.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libBaseTecDriver.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libBaseTecDriver.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "S:/tools/Linaro/gcc-linaro-arm-linux-gnueabihf-4.8-2013.09/bin/arm-linux-gnueabihf-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libBaseTecDriver.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/assembler" TYPE DIRECTORY FILES "C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/source/BaseTecDriver/assembler/" FILES_MATCHING REGEX "/[^/]*\\.asm$")
endif()

