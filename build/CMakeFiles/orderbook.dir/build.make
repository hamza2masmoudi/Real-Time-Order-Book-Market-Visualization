# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hamza/orderbook-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hamza/orderbook-project/build

# Include any dependencies generated for this target.
include CMakeFiles/orderbook.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/orderbook.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/orderbook.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/orderbook.dir/flags.make

qrc_resources.cpp: /Users/hamza/orderbook-project/resources.qrc
qrc_resources.cpp: /Users/hamza/orderbook-project/myStyles.qss
qrc_resources.cpp: resources.qrc.depends
qrc_resources.cpp: /opt/homebrew/opt/qt@6/share/qt/libexec/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating qrc_resources.cpp"
	/opt/homebrew/opt/qt@6/share/qt/libexec/rcc --name resources --output /Users/hamza/orderbook-project/build/qrc_resources.cpp /Users/hamza/orderbook-project/resources.qrc

orderbook_autogen/timestamp: /opt/homebrew/opt/qt@6/share/qt/libexec/moc
orderbook_autogen/timestamp: /opt/homebrew/opt/qt@6/share/qt/libexec/uic
orderbook_autogen/timestamp: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Automatic MOC and UIC for target orderbook"
	/opt/homebrew/bin/cmake -E cmake_autogen /Users/hamza/orderbook-project/build/CMakeFiles/orderbook_autogen.dir/AutogenInfo.json ""
	/opt/homebrew/bin/cmake -E touch /Users/hamza/orderbook-project/build/orderbook_autogen/timestamp

CMakeFiles/orderbook.dir/codegen:
.PHONY : CMakeFiles/orderbook.dir/codegen

CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o: orderbook_autogen/mocs_compilation.cpp
CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o -MF CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o -c /Users/hamza/orderbook-project/build/orderbook_autogen/mocs_compilation.cpp

CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/build/orderbook_autogen/mocs_compilation.cpp > CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.i

CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/build/orderbook_autogen/mocs_compilation.cpp -o CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.s

CMakeFiles/orderbook.dir/main.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/main.cpp.o: /Users/hamza/orderbook-project/main.cpp
CMakeFiles/orderbook.dir/main.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/orderbook.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/main.cpp.o -MF CMakeFiles/orderbook.dir/main.cpp.o.d -o CMakeFiles/orderbook.dir/main.cpp.o -c /Users/hamza/orderbook-project/main.cpp

CMakeFiles/orderbook.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/main.cpp > CMakeFiles/orderbook.dir/main.cpp.i

CMakeFiles/orderbook.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/main.cpp -o CMakeFiles/orderbook.dir/main.cpp.s

CMakeFiles/orderbook.dir/backend/orderbook.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/backend/orderbook.cpp.o: /Users/hamza/orderbook-project/backend/orderbook.cpp
CMakeFiles/orderbook.dir/backend/orderbook.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/orderbook.dir/backend/orderbook.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/backend/orderbook.cpp.o -MF CMakeFiles/orderbook.dir/backend/orderbook.cpp.o.d -o CMakeFiles/orderbook.dir/backend/orderbook.cpp.o -c /Users/hamza/orderbook-project/backend/orderbook.cpp

CMakeFiles/orderbook.dir/backend/orderbook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/backend/orderbook.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/backend/orderbook.cpp > CMakeFiles/orderbook.dir/backend/orderbook.cpp.i

CMakeFiles/orderbook.dir/backend/orderbook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/backend/orderbook.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/backend/orderbook.cpp -o CMakeFiles/orderbook.dir/backend/orderbook.cpp.s

CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o: /Users/hamza/orderbook-project/backend/matching_engine.cpp
CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o -MF CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o.d -o CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o -c /Users/hamza/orderbook-project/backend/matching_engine.cpp

CMakeFiles/orderbook.dir/backend/matching_engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/backend/matching_engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/backend/matching_engine.cpp > CMakeFiles/orderbook.dir/backend/matching_engine.cpp.i

CMakeFiles/orderbook.dir/backend/matching_engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/backend/matching_engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/backend/matching_engine.cpp -o CMakeFiles/orderbook.dir/backend/matching_engine.cpp.s

CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o: /Users/hamza/orderbook-project/frontend/mainwindow.cpp
CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o -MF CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o.d -o CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o -c /Users/hamza/orderbook-project/frontend/mainwindow.cpp

CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/frontend/mainwindow.cpp > CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.i

CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/frontend/mainwindow.cpp -o CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.s

CMakeFiles/orderbook.dir/qrc_resources.cpp.o: CMakeFiles/orderbook.dir/flags.make
CMakeFiles/orderbook.dir/qrc_resources.cpp.o: qrc_resources.cpp
CMakeFiles/orderbook.dir/qrc_resources.cpp.o: CMakeFiles/orderbook.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/orderbook.dir/qrc_resources.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/orderbook.dir/qrc_resources.cpp.o -MF CMakeFiles/orderbook.dir/qrc_resources.cpp.o.d -o CMakeFiles/orderbook.dir/qrc_resources.cpp.o -c /Users/hamza/orderbook-project/build/qrc_resources.cpp

CMakeFiles/orderbook.dir/qrc_resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/orderbook.dir/qrc_resources.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamza/orderbook-project/build/qrc_resources.cpp > CMakeFiles/orderbook.dir/qrc_resources.cpp.i

CMakeFiles/orderbook.dir/qrc_resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/orderbook.dir/qrc_resources.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamza/orderbook-project/build/qrc_resources.cpp -o CMakeFiles/orderbook.dir/qrc_resources.cpp.s

# Object files for target orderbook
orderbook_OBJECTS = \
"CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/orderbook.dir/main.cpp.o" \
"CMakeFiles/orderbook.dir/backend/orderbook.cpp.o" \
"CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o" \
"CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o" \
"CMakeFiles/orderbook.dir/qrc_resources.cpp.o"

# External object files for target orderbook
orderbook_EXTERNAL_OBJECTS =

orderbook: CMakeFiles/orderbook.dir/orderbook_autogen/mocs_compilation.cpp.o
orderbook: CMakeFiles/orderbook.dir/main.cpp.o
orderbook: CMakeFiles/orderbook.dir/backend/orderbook.cpp.o
orderbook: CMakeFiles/orderbook.dir/backend/matching_engine.cpp.o
orderbook: CMakeFiles/orderbook.dir/frontend/mainwindow.cpp.o
orderbook: CMakeFiles/orderbook.dir/qrc_resources.cpp.o
orderbook: CMakeFiles/orderbook.dir/build.make
orderbook: /opt/homebrew/opt/qt@6/lib/QtCharts.framework/Versions/A/QtCharts
orderbook: /opt/homebrew/lib/libspdlog.1.15.1.dylib
orderbook: /opt/homebrew/opt/qt@6/lib/QtOpenGLWidgets.framework/Versions/A/QtOpenGLWidgets
orderbook: /opt/homebrew/opt/qt@6/lib/QtWidgets.framework/Versions/A/QtWidgets
orderbook: /opt/homebrew/opt/qt@6/lib/QtOpenGL.framework/Versions/A/QtOpenGL
orderbook: /opt/homebrew/opt/qt@6/lib/QtGui.framework/Versions/A/QtGui
orderbook: /opt/homebrew/opt/qt@6/lib/QtCore.framework/Versions/A/QtCore
orderbook: /opt/homebrew/lib/libfmt.11.1.3.dylib
orderbook: CMakeFiles/orderbook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hamza/orderbook-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable orderbook"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/orderbook.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/orderbook.dir/build: orderbook
.PHONY : CMakeFiles/orderbook.dir/build

CMakeFiles/orderbook.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/orderbook.dir/cmake_clean.cmake
.PHONY : CMakeFiles/orderbook.dir/clean

CMakeFiles/orderbook.dir/depend: orderbook_autogen/timestamp
CMakeFiles/orderbook.dir/depend: qrc_resources.cpp
	cd /Users/hamza/orderbook-project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hamza/orderbook-project /Users/hamza/orderbook-project /Users/hamza/orderbook-project/build /Users/hamza/orderbook-project/build /Users/hamza/orderbook-project/build/CMakeFiles/orderbook.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/orderbook.dir/depend

