# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen

# Include any dependencies generated for this target.
include CMakeFiles/stewart_platform.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stewart_platform.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stewart_platform.dir/flags.make

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o: CMakeFiles/stewart_platform.dir/flags.make
CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o: src/canopen_socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o -c /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/canopen_socket.cpp

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/canopen_socket.cpp > CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.i

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/canopen_socket.cpp -o CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.s

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.requires:

.PHONY : CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.requires

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.provides: CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/stewart_platform.dir/build.make CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.provides.build
.PHONY : CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.provides

CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.provides.build: CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o


CMakeFiles/stewart_platform.dir/src/main.cpp.o: CMakeFiles/stewart_platform.dir/flags.make
CMakeFiles/stewart_platform.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stewart_platform.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stewart_platform.dir/src/main.cpp.o -c /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/main.cpp

CMakeFiles/stewart_platform.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stewart_platform.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/main.cpp > CMakeFiles/stewart_platform.dir/src/main.cpp.i

CMakeFiles/stewart_platform.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stewart_platform.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/src/main.cpp -o CMakeFiles/stewart_platform.dir/src/main.cpp.s

CMakeFiles/stewart_platform.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/stewart_platform.dir/src/main.cpp.o.requires

CMakeFiles/stewart_platform.dir/src/main.cpp.o.provides: CMakeFiles/stewart_platform.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/stewart_platform.dir/build.make CMakeFiles/stewart_platform.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/stewart_platform.dir/src/main.cpp.o.provides

CMakeFiles/stewart_platform.dir/src/main.cpp.o.provides.build: CMakeFiles/stewart_platform.dir/src/main.cpp.o


# Object files for target stewart_platform
stewart_platform_OBJECTS = \
"CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o" \
"CMakeFiles/stewart_platform.dir/src/main.cpp.o"

# External object files for target stewart_platform
stewart_platform_EXTERNAL_OBJECTS =

stewart_platform: CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o
stewart_platform: CMakeFiles/stewart_platform.dir/src/main.cpp.o
stewart_platform: CMakeFiles/stewart_platform.dir/build.make
stewart_platform: CMakeFiles/stewart_platform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable stewart_platform"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stewart_platform.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Saving exec in bin/ directory..."
	/usr/bin/cmake -E make_directory /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/bin/UNIX/Linux_5.0.0-37-generic
	/usr/bin/cmake -E copy /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/stewart_platform /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/bin/UNIX/Linux_5.0.0-37-generic

# Rule to build all files generated by this target.
CMakeFiles/stewart_platform.dir/build: stewart_platform

.PHONY : CMakeFiles/stewart_platform.dir/build

CMakeFiles/stewart_platform.dir/requires: CMakeFiles/stewart_platform.dir/src/canopen_socket.cpp.o.requires
CMakeFiles/stewart_platform.dir/requires: CMakeFiles/stewart_platform.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/stewart_platform.dir/requires

CMakeFiles/stewart_platform.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stewart_platform.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stewart_platform.dir/clean

CMakeFiles/stewart_platform.dir/depend:
	cd /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen /home/aightech/Documents/Profesional/Isir/Service_Technique/canopen/CMakeFiles/stewart_platform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stewart_platform.dir/depend
