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
CMAKE_SOURCE_DIR = /home/nowcoder/FileServer/FileServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nowcoder/FileServer/FileServer/build

# Include any dependencies generated for this target.
include src/CMakeFiles/FileServer.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/FileServer.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/FileServer.dir/flags.make

src/CMakeFiles/FileServer.dir/main.cpp.o: src/CMakeFiles/FileServer.dir/flags.make
src/CMakeFiles/FileServer.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nowcoder/FileServer/FileServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/FileServer.dir/main.cpp.o"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FileServer.dir/main.cpp.o -c /home/nowcoder/FileServer/FileServer/src/main.cpp

src/CMakeFiles/FileServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileServer.dir/main.cpp.i"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nowcoder/FileServer/FileServer/src/main.cpp > CMakeFiles/FileServer.dir/main.cpp.i

src/CMakeFiles/FileServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileServer.dir/main.cpp.s"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nowcoder/FileServer/FileServer/src/main.cpp -o CMakeFiles/FileServer.dir/main.cpp.s

src/CMakeFiles/FileServer.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/FileServer.dir/main.cpp.o.requires

src/CMakeFiles/FileServer.dir/main.cpp.o.provides: src/CMakeFiles/FileServer.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/FileServer.dir/build.make src/CMakeFiles/FileServer.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/FileServer.dir/main.cpp.o.provides

src/CMakeFiles/FileServer.dir/main.cpp.o.provides.build: src/CMakeFiles/FileServer.dir/main.cpp.o


src/CMakeFiles/FileServer.dir/server.cpp.o: src/CMakeFiles/FileServer.dir/flags.make
src/CMakeFiles/FileServer.dir/server.cpp.o: ../src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nowcoder/FileServer/FileServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/FileServer.dir/server.cpp.o"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FileServer.dir/server.cpp.o -c /home/nowcoder/FileServer/FileServer/src/server.cpp

src/CMakeFiles/FileServer.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileServer.dir/server.cpp.i"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nowcoder/FileServer/FileServer/src/server.cpp > CMakeFiles/FileServer.dir/server.cpp.i

src/CMakeFiles/FileServer.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileServer.dir/server.cpp.s"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nowcoder/FileServer/FileServer/src/server.cpp -o CMakeFiles/FileServer.dir/server.cpp.s

src/CMakeFiles/FileServer.dir/server.cpp.o.requires:

.PHONY : src/CMakeFiles/FileServer.dir/server.cpp.o.requires

src/CMakeFiles/FileServer.dir/server.cpp.o.provides: src/CMakeFiles/FileServer.dir/server.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/FileServer.dir/build.make src/CMakeFiles/FileServer.dir/server.cpp.o.provides.build
.PHONY : src/CMakeFiles/FileServer.dir/server.cpp.o.provides

src/CMakeFiles/FileServer.dir/server.cpp.o.provides.build: src/CMakeFiles/FileServer.dir/server.cpp.o


src/CMakeFiles/FileServer.dir/threadpool.cpp.o: src/CMakeFiles/FileServer.dir/flags.make
src/CMakeFiles/FileServer.dir/threadpool.cpp.o: ../src/threadpool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nowcoder/FileServer/FileServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/FileServer.dir/threadpool.cpp.o"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FileServer.dir/threadpool.cpp.o -c /home/nowcoder/FileServer/FileServer/src/threadpool.cpp

src/CMakeFiles/FileServer.dir/threadpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileServer.dir/threadpool.cpp.i"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nowcoder/FileServer/FileServer/src/threadpool.cpp > CMakeFiles/FileServer.dir/threadpool.cpp.i

src/CMakeFiles/FileServer.dir/threadpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileServer.dir/threadpool.cpp.s"
	cd /home/nowcoder/FileServer/FileServer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nowcoder/FileServer/FileServer/src/threadpool.cpp -o CMakeFiles/FileServer.dir/threadpool.cpp.s

src/CMakeFiles/FileServer.dir/threadpool.cpp.o.requires:

.PHONY : src/CMakeFiles/FileServer.dir/threadpool.cpp.o.requires

src/CMakeFiles/FileServer.dir/threadpool.cpp.o.provides: src/CMakeFiles/FileServer.dir/threadpool.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/FileServer.dir/build.make src/CMakeFiles/FileServer.dir/threadpool.cpp.o.provides.build
.PHONY : src/CMakeFiles/FileServer.dir/threadpool.cpp.o.provides

src/CMakeFiles/FileServer.dir/threadpool.cpp.o.provides.build: src/CMakeFiles/FileServer.dir/threadpool.cpp.o


# Object files for target FileServer
FileServer_OBJECTS = \
"CMakeFiles/FileServer.dir/main.cpp.o" \
"CMakeFiles/FileServer.dir/server.cpp.o" \
"CMakeFiles/FileServer.dir/threadpool.cpp.o"

# External object files for target FileServer
FileServer_EXTERNAL_OBJECTS =

bin/FileServer: src/CMakeFiles/FileServer.dir/main.cpp.o
bin/FileServer: src/CMakeFiles/FileServer.dir/server.cpp.o
bin/FileServer: src/CMakeFiles/FileServer.dir/threadpool.cpp.o
bin/FileServer: src/CMakeFiles/FileServer.dir/build.make
bin/FileServer: tool/libToolLib.a
bin/FileServer: tool/libToolLib.a
bin/FileServer: src/CMakeFiles/FileServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nowcoder/FileServer/FileServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/FileServer"
	cd /home/nowcoder/FileServer/FileServer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FileServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/FileServer.dir/build: bin/FileServer

.PHONY : src/CMakeFiles/FileServer.dir/build

src/CMakeFiles/FileServer.dir/requires: src/CMakeFiles/FileServer.dir/main.cpp.o.requires
src/CMakeFiles/FileServer.dir/requires: src/CMakeFiles/FileServer.dir/server.cpp.o.requires
src/CMakeFiles/FileServer.dir/requires: src/CMakeFiles/FileServer.dir/threadpool.cpp.o.requires

.PHONY : src/CMakeFiles/FileServer.dir/requires

src/CMakeFiles/FileServer.dir/clean:
	cd /home/nowcoder/FileServer/FileServer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/FileServer.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/FileServer.dir/clean

src/CMakeFiles/FileServer.dir/depend:
	cd /home/nowcoder/FileServer/FileServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nowcoder/FileServer/FileServer /home/nowcoder/FileServer/FileServer/src /home/nowcoder/FileServer/FileServer/build /home/nowcoder/FileServer/FileServer/build/src /home/nowcoder/FileServer/FileServer/build/src/CMakeFiles/FileServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/FileServer.dir/depend

