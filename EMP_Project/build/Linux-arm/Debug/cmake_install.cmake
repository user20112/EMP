# Install script for directory: S:/work/AsymtecUnloader

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "S:/work/AsymtecUnloader/install/Linux-arm/Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/PugiXML/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/GaAppBaseLib/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/GaGCppAPI/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/BeagleBoneResources/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/GaApp/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/BaseTecDriver/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/AsymtecUnloader/cmake_install.cmake")
  include("S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/KleberMqtt/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "S:/work/AsymtecUnloader/build/Linux-arm/Debug/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "S:/work/AsymtecUnloader/build/Linux-arm/Debug/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
