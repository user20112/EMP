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
CMAKE_SOURCE_DIR = S:\work\AsymtecUnloader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = S:\work\AsymtecUnloader\build\Linux-arm\Debug

# Utility rule file for docXLSDispenser.

# Include the progress variables for this target.
include source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/progress.make

source/AsymtecUnloader/CMakeFiles/docXLSDispenser:
	cd /d S:\work\AsymtecUnloader\source\AsymtecUnloader\documentation && sh /cygdrive/S/Scripts/buildDocumentation.sh S:/work/AsymtecUnloader/source/AsymtecUnloader/documentation/XLSDispenser.doxyfile S:/work/AsymtecUnloader/build/Linux-arm/Debug/source/AsymtecUnloader/doc S:/work/AsymtecUnloader/install/Linux-arm/Debug/doc/XLSDispenser

docXLSDispenser: source/AsymtecUnloader/CMakeFiles/docXLSDispenser
docXLSDispenser: source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/build.make
.PHONY : docXLSDispenser

# Rule to build all files generated by this target.
source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/build: docXLSDispenser
.PHONY : source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/build

source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/clean:
	cd /d S:\work\AsymtecUnloader\build\Linux-arm\Debug\source\AsymtecUnloader && $(CMAKE_COMMAND) -P CMakeFiles\docXLSDispenser.dir\cmake_clean.cmake
.PHONY : source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/clean

source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" S:\work\AsymtecUnloader S:\work\AsymtecUnloader\source\AsymtecUnloader S:\work\AsymtecUnloader\build\Linux-arm\Debug S:\work\AsymtecUnloader\build\Linux-arm\Debug\source\AsymtecUnloader S:\work\AsymtecUnloader\build\Linux-arm\Debug\source\AsymtecUnloader\CMakeFiles\docXLSDispenser.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : source/AsymtecUnloader/CMakeFiles/docXLSDispenser.dir/depend
