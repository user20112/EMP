# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = S:\tools\CMake\bin\cmake.exe

# The command to remove a file.
RM = S:\tools\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug

# Utility rule file for docHwAccessDemo.

# Include the progress variables for this target.
include source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/progress.make

source/HwAccessDemo/CMakeFiles/docHwAccessDemo:
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\HwAccessDemo\documentation && sh /cygdrive/S/Scripts/buildDocumentation.sh C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/source/HwAccessDemo/documentation/HwAccessDemo.doxyfile C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/HwAccessDemo/doc C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/Install/Linux-arm/Debug/doc/HwAccessDemo

docHwAccessDemo: source/HwAccessDemo/CMakeFiles/docHwAccessDemo
docHwAccessDemo: source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/build.make
.PHONY : docHwAccessDemo

# Rule to build all files generated by this target.
source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/build: docHwAccessDemo
.PHONY : source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/build

source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/clean:
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\HwAccessDemo && $(CMAKE_COMMAND) -P CMakeFiles\docHwAccessDemo.dir\cmake_clean.cmake
.PHONY : source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/clean

source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\HwAccessDemo C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\HwAccessDemo C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\HwAccessDemo\CMakeFiles\docHwAccessDemo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : source/HwAccessDemo/CMakeFiles/docHwAccessDemo.dir/depend
