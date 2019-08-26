# Install script for directory: C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/PugiXML/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/GaAppBaseLib/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/GaGCppAPI/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/BeagleBoneResources/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/GaApp/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/BaseTecDriver/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/HwAccessDemo/cmake_install.cmake")
  include("C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/KleberMqtt/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
