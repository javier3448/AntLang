# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/javier/Dropbox/MyProjects/MyLanguage/AntLang

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build

# Include any dependencies generated for this target.
include CMakeFiles/AntLang.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AntLang.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AntLang.dir/flags.make

CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o: ../src/Parser/astexpression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/astexpression.cpp

CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/astexpression.cpp > CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.i

CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/astexpression.cpp -o CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.s

CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o: ../src/Parser/grapher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/grapher.cpp

CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/grapher.cpp > CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.i

CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/grapher.cpp -o CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.s

CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o: ../src/Parser/lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/lexer.cpp

CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/lexer.cpp > CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.i

CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/lexer.cpp -o CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.s

CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o: ../src/Parser/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/parser.cpp

CMakeFiles/AntLang.dir/src/Parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/parser.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/parser.cpp > CMakeFiles/AntLang.dir/src/Parser/parser.cpp.i

CMakeFiles/AntLang.dir/src/Parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/parser.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/parser.cpp -o CMakeFiles/AntLang.dir/src/Parser/parser.cpp.s

CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o: ../src/Parser/shuntingyard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/shuntingyard.cpp

CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/shuntingyard.cpp > CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.i

CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/shuntingyard.cpp -o CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.s

CMakeFiles/AntLang.dir/src/Parser/token.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/token.cpp.o: ../src/Parser/token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/token.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/token.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/token.cpp

CMakeFiles/AntLang.dir/src/Parser/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/token.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/token.cpp > CMakeFiles/AntLang.dir/src/Parser/token.cpp.i

CMakeFiles/AntLang.dir/src/Parser/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/token.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/token.cpp -o CMakeFiles/AntLang.dir/src/Parser/token.cpp.s

CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o: ../src/Parser/tokencache.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/tokencache.cpp

CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/tokencache.cpp > CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.i

CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/Parser/tokencache.cpp -o CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.s

CMakeFiles/AntLang.dir/src/main.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/AntLang.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/main.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/main.cpp

CMakeFiles/AntLang.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/main.cpp > CMakeFiles/AntLang.dir/src/main.cpp.i

CMakeFiles/AntLang.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/main.cpp -o CMakeFiles/AntLang.dir/src/main.cpp.s

CMakeFiles/AntLang.dir/src/mystring.cpp.o: CMakeFiles/AntLang.dir/flags.make
CMakeFiles/AntLang.dir/src/mystring.cpp.o: ../src/mystring.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/AntLang.dir/src/mystring.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AntLang.dir/src/mystring.cpp.o -c /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/mystring.cpp

CMakeFiles/AntLang.dir/src/mystring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AntLang.dir/src/mystring.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/mystring.cpp > CMakeFiles/AntLang.dir/src/mystring.cpp.i

CMakeFiles/AntLang.dir/src/mystring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AntLang.dir/src/mystring.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/src/mystring.cpp -o CMakeFiles/AntLang.dir/src/mystring.cpp.s

# Object files for target AntLang
AntLang_OBJECTS = \
"CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/token.cpp.o" \
"CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o" \
"CMakeFiles/AntLang.dir/src/main.cpp.o" \
"CMakeFiles/AntLang.dir/src/mystring.cpp.o"

# External object files for target AntLang
AntLang_EXTERNAL_OBJECTS =

AntLang: CMakeFiles/AntLang.dir/src/Parser/astexpression.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/grapher.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/lexer.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/parser.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/shuntingyard.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/token.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/Parser/tokencache.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/main.cpp.o
AntLang: CMakeFiles/AntLang.dir/src/mystring.cpp.o
AntLang: CMakeFiles/AntLang.dir/build.make
AntLang: CMakeFiles/AntLang.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable AntLang"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AntLang.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AntLang.dir/build: AntLang

.PHONY : CMakeFiles/AntLang.dir/build

CMakeFiles/AntLang.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AntLang.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AntLang.dir/clean

CMakeFiles/AntLang.dir/depend:
	cd /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Dropbox/MyProjects/MyLanguage/AntLang /home/javier/Dropbox/MyProjects/MyLanguage/AntLang /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build /home/javier/Dropbox/MyProjects/MyLanguage/AntLang/build/CMakeFiles/AntLang.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AntLang.dir/depend

