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

# Include any dependencies generated for this target.
include source/KleberMqtt/CMakeFiles/KleberMqtt.dir/depend.make

# Include the progress variables for this target.
include source/KleberMqtt/CMakeFiles/KleberMqtt.dir/progress.make

# Include the compile flags for this target's objects.
include source/KleberMqtt/CMakeFiles/KleberMqtt.dir/flags.make

source/KleberMqtt/ModuleVersionInfo.cpp: ../../../source/KleberMqtt/src/ModuleVersionInfo.template.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ModuleVersionInfo.cpp"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt && sh /cygdrive/S/Scripts/buildVersion.sh src/ModuleVersionInfo.template.cpp C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/KleberMqtt/ModuleVersionInfo.cpp

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/flags.make
source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o: ../../../source/KleberMqtt/src/KleberMqtt.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\KleberMqtt.dir\src\KleberMqtt.cpp.o -c C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt\src\KleberMqtt.cpp

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.i"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt\src\KleberMqtt.cpp > CMakeFiles\KleberMqtt.dir\src\KleberMqtt.cpp.i

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.s"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt\src\KleberMqtt.cpp -o CMakeFiles\KleberMqtt.dir\src\KleberMqtt.cpp.s

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.requires:
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.requires

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.provides: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.requires
	$(MAKE) -f source\KleberMqtt\CMakeFiles\KleberMqtt.dir\build.make source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.provides.build
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.provides

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.provides.build: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/flags.make
source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o: source/KleberMqtt/ModuleVersionInfo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\KleberMqtt.dir\ModuleVersionInfo.cpp.o -c C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt\ModuleVersionInfo.cpp

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.i"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt\ModuleVersionInfo.cpp > CMakeFiles\KleberMqtt.dir\ModuleVersionInfo.cpp.i

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.s"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && S:\tools\Linaro\gcc-linaro-arm-linux-gnueabihf-4.8-2013.09\bin\arm-linux-gnueabihf-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt\ModuleVersionInfo.cpp -o CMakeFiles\KleberMqtt.dir\ModuleVersionInfo.cpp.s

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.requires:
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.requires

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.provides: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.requires
	$(MAKE) -f source\KleberMqtt\CMakeFiles\KleberMqtt.dir\build.make source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.provides.build
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.provides

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.provides.build: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o

# Object files for target KleberMqtt
KleberMqtt_OBJECTS = \
"CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o" \
"CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o"

# External object files for target KleberMqtt
KleberMqtt_EXTERNAL_OBJECTS =

source/KleberMqtt/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o
source/KleberMqtt/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o
source/KleberMqtt/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/build.make
source/KleberMqtt/libKleberMqtt.so: source/PugiXML/libPugiXML.so
source/KleberMqtt/libKleberMqtt.so: source/GaAppBaseLib/libGaAppBaseLib.so
source/KleberMqtt/libKleberMqtt.so: source/GaGCppAPI/libGaGCppAPI.so
source/KleberMqtt/libKleberMqtt.so: s:/tools/paho/lib/libpaho-mqtt3a.so
source/KleberMqtt/libKleberMqtt.so: s:/tools/paho/lib/libpaho-mqtt3c.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/ncurses/lib/libncurses.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/ncurses/lib/libform.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/ncurses/lib/libmenu.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/ncurses/lib/libpanel.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/ncurses/lib/libtinfo.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/jansson/lib/libjansson.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_system.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_regex.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_thread.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgasched.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaapi.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgacommon.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaCRpc.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaCUtil.so
source/KleberMqtt/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libTLSF.so
source/KleberMqtt/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libKleberMqtt.so"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt && sh /cygdrive/S/Scripts/buildVersion.sh src/ModuleVersionInfo.template.cpp C:/Users/d.paddock/Documents/GitHub/EMP/EMP_Project/build/Linux-arm/Debug/source/KleberMqtt/ModuleVersionInfo.cpp
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\KleberMqtt.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/KleberMqtt/CMakeFiles/KleberMqtt.dir/build: source/KleberMqtt/libKleberMqtt.so
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/build

# Object files for target KleberMqtt
KleberMqtt_OBJECTS = \
"CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o" \
"CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o"

# External object files for target KleberMqtt
KleberMqtt_EXTERNAL_OBJECTS =

source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/build.make
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/PugiXML/libPugiXML.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/GaAppBaseLib/libGaAppBaseLib.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/GaGCppAPI/libGaGCppAPI.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: s:/tools/paho/lib/libpaho-mqtt3a.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: s:/tools/paho/lib/libpaho-mqtt3c.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/ncurses/lib/libncurses.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/ncurses/lib/libform.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/ncurses/lib/libmenu.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/ncurses/lib/libpanel.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/ncurses/lib/libtinfo.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/jansson/lib/libjansson.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_system.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_regex.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/boost/1.58.0/bin/Linux/armhf/libboost_thread.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgasched.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaapi.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgacommon.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaCRpc.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libgaCUtil.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: S:/tools/gamma/target/linux/armhf/lib/libTLSF.so
source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library CMakeFiles\CMakeRelink.dir\libKleberMqtt.so"
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\KleberMqtt.dir\relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
source/KleberMqtt/CMakeFiles/KleberMqtt.dir/preinstall: source/KleberMqtt/CMakeFiles/CMakeRelink.dir/libKleberMqtt.so
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/preinstall

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/requires: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/src/KleberMqtt.cpp.o.requires
source/KleberMqtt/CMakeFiles/KleberMqtt.dir/requires: source/KleberMqtt/CMakeFiles/KleberMqtt.dir/ModuleVersionInfo.cpp.o.requires
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/requires

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/clean:
	cd /d C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt && $(CMAKE_COMMAND) -P CMakeFiles\KleberMqtt.dir\cmake_clean.cmake
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/clean

source/KleberMqtt/CMakeFiles/KleberMqtt.dir/depend: source/KleberMqtt/ModuleVersionInfo.cpp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\source\KleberMqtt C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt C:\Users\d.paddock\Documents\GitHub\EMP\EMP_Project\build\Linux-arm\Debug\source\KleberMqtt\CMakeFiles\KleberMqtt.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : source/KleberMqtt/CMakeFiles/KleberMqtt.dir/depend

