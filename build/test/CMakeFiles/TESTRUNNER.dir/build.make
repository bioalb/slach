# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alberto/code/slach

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alberto/code/slach

# Include any dependencies generated for this target.
include build/test/CMakeFiles/TESTRUNNER.dir/depend.make

# Include the progress variables for this target.
include build/test/CMakeFiles/TESTRUNNER.dir/progress.make

# Include the compile flags for this target's objects.
include build/test/CMakeFiles/TESTRUNNER.dir/flags.make

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o: build/test/CMakeFiles/TESTRUNNER.dir/flags.make
build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o: test/test_runner.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alberto/code/slach/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o -c /home/alberto/code/slach/test/test_runner.cpp

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.i"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alberto/code/slach/test/test_runner.cpp > CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.i

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.s"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alberto/code/slach/test/test_runner.cpp -o CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.s

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.requires:
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.requires

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.provides: build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.requires
	$(MAKE) -f build/test/CMakeFiles/TESTRUNNER.dir/build.make build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.provides.build
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.provides

build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.provides.build: build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o: build/test/CMakeFiles/TESTRUNNER.dir/flags.make
build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o: src/Exception.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alberto/code/slach/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o -c /home/alberto/code/slach/src/Exception.cpp

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.i"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alberto/code/slach/src/Exception.cpp > CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.i

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.s"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alberto/code/slach/src/Exception.cpp -o CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.s

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.requires:
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.requires

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.provides: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.requires
	$(MAKE) -f build/test/CMakeFiles/TESTRUNNER.dir/build.make build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.provides.build
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.provides

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.provides.build: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o: build/test/CMakeFiles/TESTRUNNER.dir/flags.make
build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o: src/Square.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alberto/code/slach/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o -c /home/alberto/code/slach/src/Square.cpp

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.i"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alberto/code/slach/src/Square.cpp > CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.i

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.s"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alberto/code/slach/src/Square.cpp -o CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.s

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.requires:
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.requires

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.provides: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.requires
	$(MAKE) -f build/test/CMakeFiles/TESTRUNNER.dir/build.make build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.provides.build
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.provides

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.provides.build: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o: build/test/CMakeFiles/TESTRUNNER.dir/flags.make
build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o: src/ChessBoard.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alberto/code/slach/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o -c /home/alberto/code/slach/src/ChessBoard.cpp

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.i"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alberto/code/slach/src/ChessBoard.cpp > CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.i

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.s"
	cd /home/alberto/code/slach/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alberto/code/slach/src/ChessBoard.cpp -o CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.s

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.requires:
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.requires

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.provides: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.requires
	$(MAKE) -f build/test/CMakeFiles/TESTRUNNER.dir/build.make build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.provides.build
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.provides

build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.provides.build: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o

test/test_runner.cpp:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alberto/code/slach/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "running cxxtestgen now..."
	cd /home/alberto/code/slach/build/test && ../../test/cxxtest/bin/cxxtestgen --error-printer -o /home/alberto/code/slach/test/test_runner.cpp /home/alberto/code/slach/test/TestChessboard.hpp /home/alberto/code/slach/test/TestPosition.hpp

# Object files for target TESTRUNNER
TESTRUNNER_OBJECTS = \
"CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o" \
"CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o" \
"CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o" \
"CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o"

# External object files for target TESTRUNNER
TESTRUNNER_EXTERNAL_OBJECTS =

build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o
build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o
build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o
build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o
build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/build.make
build/test/TESTRUNNER: build/test/CMakeFiles/TESTRUNNER.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TESTRUNNER"
	cd /home/alberto/code/slach/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TESTRUNNER.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
build/test/CMakeFiles/TESTRUNNER.dir/build: build/test/TESTRUNNER
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/build

build/test/CMakeFiles/TESTRUNNER.dir/requires: build/test/CMakeFiles/TESTRUNNER.dir/__/__/test/test_runner.cpp.o.requires
build/test/CMakeFiles/TESTRUNNER.dir/requires: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Exception.cpp.o.requires
build/test/CMakeFiles/TESTRUNNER.dir/requires: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/Square.cpp.o.requires
build/test/CMakeFiles/TESTRUNNER.dir/requires: build/test/CMakeFiles/TESTRUNNER.dir/__/__/src/ChessBoard.cpp.o.requires
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/requires

build/test/CMakeFiles/TESTRUNNER.dir/clean:
	cd /home/alberto/code/slach/build/test && $(CMAKE_COMMAND) -P CMakeFiles/TESTRUNNER.dir/cmake_clean.cmake
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/clean

build/test/CMakeFiles/TESTRUNNER.dir/depend: test/test_runner.cpp
	cd /home/alberto/code/slach && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alberto/code/slach /home/alberto/code/slach/build/test /home/alberto/code/slach /home/alberto/code/slach/build/test /home/alberto/code/slach/build/test/CMakeFiles/TESTRUNNER.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : build/test/CMakeFiles/TESTRUNNER.dir/depend

