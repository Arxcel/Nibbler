# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vkozlov/Documents/nibbler_game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vkozlov/Documents/nibbler_game/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Nibbler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Nibbler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Nibbler.dir/flags.make

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o: ../nibbler_glfw/src/nibbler_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vkozlov/Documents/nibbler_game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o -c /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/nibbler_glfw.cpp

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/nibbler_glfw.cpp > CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.i

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/nibbler_glfw.cpp -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.s

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.requires:

.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.requires

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.provides: CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.requires
	$(MAKE) -f CMakeFiles/Nibbler.dir/build.make CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.provides.build
.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.provides

CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.provides.build: CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o


CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o: ../nibbler_glfw/src/Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vkozlov/Documents/nibbler_game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o -c /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Shader.cpp

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Shader.cpp > CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.i

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Shader.cpp -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.s

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.requires:

.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.requires

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.provides: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/Nibbler.dir/build.make CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.provides.build
.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.provides

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.provides.build: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o


CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o: ../nibbler_glfw/src/Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vkozlov/Documents/nibbler_game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o -c /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Texture.cpp

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Texture.cpp > CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.i

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vkozlov/Documents/nibbler_game/nibbler_glfw/src/Texture.cpp -o CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.s

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.requires:

.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.requires

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.provides: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/Nibbler.dir/build.make CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.provides.build
.PHONY : CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.provides

CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.provides.build: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o


# Object files for target Nibbler
Nibbler_OBJECTS = \
"CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o" \
"CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o" \
"CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o"

# External object files for target Nibbler
Nibbler_EXTERNAL_OBJECTS =

Nibbler: CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/build.make
Nibbler: CMakeFiles/Nibbler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vkozlov/Documents/nibbler_game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Nibbler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Nibbler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Nibbler.dir/build: Nibbler

.PHONY : CMakeFiles/Nibbler.dir/build

CMakeFiles/Nibbler.dir/requires: CMakeFiles/Nibbler.dir/nibbler_glfw/src/nibbler_glfw.cpp.o.requires
CMakeFiles/Nibbler.dir/requires: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Shader.cpp.o.requires
CMakeFiles/Nibbler.dir/requires: CMakeFiles/Nibbler.dir/nibbler_glfw/src/Texture.cpp.o.requires

.PHONY : CMakeFiles/Nibbler.dir/requires

CMakeFiles/Nibbler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nibbler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nibbler.dir/clean

CMakeFiles/Nibbler.dir/depend:
	cd /Users/vkozlov/Documents/nibbler_game/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vkozlov/Documents/nibbler_game /Users/vkozlov/Documents/nibbler_game /Users/vkozlov/Documents/nibbler_game/cmake-build-debug /Users/vkozlov/Documents/nibbler_game/cmake-build-debug /Users/vkozlov/Documents/nibbler_game/cmake-build-debug/CMakeFiles/Nibbler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nibbler.dir/depend

