# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_SOURCE_DIR = /home/tborras/exaro/exaro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tborras/exaro/exaro/build

# Include any dependencies generated for this target.
include plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/depend.make

# Include the progress variables for this target.
include plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/flags.make

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/flags.make
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o: ../plugins/report/items/charts/piechart/piechart.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Piechart.dir/piechart.cpp.o -c /home/tborras/exaro/exaro/plugins/report/items/charts/piechart/piechart.cpp

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Piechart.dir/piechart.cpp.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/plugins/report/items/charts/piechart/piechart.cpp > CMakeFiles/Piechart.dir/piechart.cpp.i

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Piechart.dir/piechart.cpp.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/plugins/report/items/charts/piechart/piechart.cpp -o CMakeFiles/Piechart.dir/piechart.cpp.s

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.requires:
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.requires

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.provides: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.requires
	$(MAKE) -f plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build.make plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.provides.build
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.provides

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.provides.build: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.provides.build

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/flags.make
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o: plugins/report/items/charts/piechart/moc_piechart.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Piechart.dir/moc_piechart.cxx.o -c /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/moc_piechart.cxx

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Piechart.dir/moc_piechart.cxx.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/moc_piechart.cxx > CMakeFiles/Piechart.dir/moc_piechart.cxx.i

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Piechart.dir/moc_piechart.cxx.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/moc_piechart.cxx -o CMakeFiles/Piechart.dir/moc_piechart.cxx.s

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.requires:
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.requires

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.provides: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.requires
	$(MAKE) -f plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build.make plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.provides.build
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.provides

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.provides.build: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.provides.build

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/flags.make
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o: plugins/report/items/charts/piechart/qrc_piechart.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Piechart.dir/qrc_piechart.cxx.o -c /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/qrc_piechart.cxx

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Piechart.dir/qrc_piechart.cxx.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/qrc_piechart.cxx > CMakeFiles/Piechart.dir/qrc_piechart.cxx.i

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Piechart.dir/qrc_piechart.cxx.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/qrc_piechart.cxx -o CMakeFiles/Piechart.dir/qrc_piechart.cxx.s

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.requires:
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.requires

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.provides: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.requires
	$(MAKE) -f plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build.make plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.provides.build
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.provides

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.provides.build: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.provides.build

plugins/report/items/charts/piechart/moc_piechart.cxx: ../plugins/report/items/charts/piechart/piechart.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_piechart.cxx"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/moc-qt4 -I/home/tborras/exaro/exaro/plugins/report/items/charts/chartinterface -I/home/tborras/exaro/exaro/libs/report -I/usr/include/qt4 -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtCore -I/home/tborras/exaro/exaro -I/home/tborras/exaro/exaro/build -DEXARO_VERSION="2.0.0" -DQT_OPENGL_LIB -DQT_SCRIPT_LIB -DQT_UITOOLS_LIB -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_XML_LIB -DQT_SQL_LIB -DQT_CORE_LIB -DLIB_INSTALL_DIR="/usr/local/lib" -o /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/moc_piechart.cxx /home/tborras/exaro/exaro/plugins/report/items/charts/piechart/piechart.h

plugins/report/items/charts/piechart/qrc_piechart.cxx: ../plugins/report/items/charts/piechart/piechart.png
plugins/report/items/charts/piechart/qrc_piechart.cxx: ../plugins/report/items/charts/piechart/piechart.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_piechart.cxx"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && /usr/bin/rcc -name piechart -o /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/qrc_piechart.cxx /home/tborras/exaro/exaro/plugins/report/items/charts/piechart/piechart.qrc

# Object files for target Piechart
Piechart_OBJECTS = \
"CMakeFiles/Piechart.dir/piechart.cpp.o" \
"CMakeFiles/Piechart.dir/moc_piechart.cxx.o" \
"CMakeFiles/Piechart.dir/qrc_piechart.cxx.o"

# External object files for target Piechart
Piechart_EXTERNAL_OBJECTS =

plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o
plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o
plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o
plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/chartinterface/libChartInterface.a
plugins/report/items/charts/piechart/libPiechart.so: libs/report/libReport.so.2.0.0
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtOpenGL.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtScript.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtUiTools.a
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtWebKit.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtGui.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtXml.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtSql.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtXmlPatterns.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtNetwork.so
plugins/report/items/charts/piechart/libPiechart.so: /usr/lib/libQtCore.so
plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build.make
plugins/report/items/charts/piechart/libPiechart.so: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libPiechart.so"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Piechart.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build: plugins/report/items/charts/piechart/libPiechart.so
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/build

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/requires: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/piechart.cpp.o.requires
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/requires: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/moc_piechart.cxx.o.requires
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/requires: plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/qrc_piechart.cxx.o.requires
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/requires

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/clean:
	cd /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart && $(CMAKE_COMMAND) -P CMakeFiles/Piechart.dir/cmake_clean.cmake
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/clean

plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/depend: plugins/report/items/charts/piechart/moc_piechart.cxx
plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/depend: plugins/report/items/charts/piechart/qrc_piechart.cxx
	cd /home/tborras/exaro/exaro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tborras/exaro/exaro /home/tborras/exaro/exaro/plugins/report/items/charts/piechart /home/tborras/exaro/exaro/build /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart /home/tborras/exaro/exaro/build/plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/report/items/charts/piechart/CMakeFiles/Piechart.dir/depend
