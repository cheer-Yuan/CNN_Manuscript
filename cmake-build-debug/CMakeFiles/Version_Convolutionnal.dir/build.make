# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/100/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/100/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Version_Convolutionnal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Version_Convolutionnal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Version_Convolutionnal.dir/flags.make

CMakeFiles/Version_Convolutionnal.dir/main.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Version_Convolutionnal.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/main.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/main.c

CMakeFiles/Version_Convolutionnal.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/main.c > CMakeFiles/Version_Convolutionnal.dir/main.c.i

CMakeFiles/Version_Convolutionnal.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/main.c -o CMakeFiles/Version_Convolutionnal.dir/main.c.s

CMakeFiles/Version_Convolutionnal.dir/cnn.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/cnn.c.o: ../cnn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Version_Convolutionnal.dir/cnn.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/cnn.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn.c

CMakeFiles/Version_Convolutionnal.dir/cnn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/cnn.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn.c > CMakeFiles/Version_Convolutionnal.dir/cnn.c.i

CMakeFiles/Version_Convolutionnal.dir/cnn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/cnn.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn.c -o CMakeFiles/Version_Convolutionnal.dir/cnn.c.s

CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o: ../data_Images.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/data_Images.c

CMakeFiles/Version_Convolutionnal.dir/data_Images.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/data_Images.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/data_Images.c > CMakeFiles/Version_Convolutionnal.dir/data_Images.c.i

CMakeFiles/Version_Convolutionnal.dir/data_Images.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/data_Images.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/data_Images.c -o CMakeFiles/Version_Convolutionnal.dir/data_Images.c.s

CMakeFiles/Version_Convolutionnal.dir/mat.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/mat.c.o: ../mat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Version_Convolutionnal.dir/mat.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/mat.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/mat.c

CMakeFiles/Version_Convolutionnal.dir/mat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/mat.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/mat.c > CMakeFiles/Version_Convolutionnal.dir/mat.c.i

CMakeFiles/Version_Convolutionnal.dir/mat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/mat.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/mat.c -o CMakeFiles/Version_Convolutionnal.dir/mat.c.s

CMakeFiles/Version_Convolutionnal.dir/test.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Version_Convolutionnal.dir/test.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/test.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/test.c

CMakeFiles/Version_Convolutionnal.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/test.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/test.c > CMakeFiles/Version_Convolutionnal.dir/test.c.i

CMakeFiles/Version_Convolutionnal.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/test.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/test.c -o CMakeFiles/Version_Convolutionnal.dir/test.c.s

CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o: CMakeFiles/Version_Convolutionnal.dir/flags.make
CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o: ../cnn_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o   -c /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn_1.c

CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn_1.c > CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.i

CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cnn_1.c -o CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.s

# Object files for target Version_Convolutionnal
Version_Convolutionnal_OBJECTS = \
"CMakeFiles/Version_Convolutionnal.dir/main.c.o" \
"CMakeFiles/Version_Convolutionnal.dir/cnn.c.o" \
"CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o" \
"CMakeFiles/Version_Convolutionnal.dir/mat.c.o" \
"CMakeFiles/Version_Convolutionnal.dir/test.c.o" \
"CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o"

# External object files for target Version_Convolutionnal
Version_Convolutionnal_EXTERNAL_OBJECTS =

Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/main.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/cnn.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/data_Images.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/mat.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/test.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/cnn_1.c.o
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/build.make
Version_Convolutionnal: CMakeFiles/Version_Convolutionnal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Version_Convolutionnal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Version_Convolutionnal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Version_Convolutionnal.dir/build: Version_Convolutionnal

.PHONY : CMakeFiles/Version_Convolutionnal.dir/build

CMakeFiles/Version_Convolutionnal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Version_Convolutionnal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Version_Convolutionnal.dir/clean

CMakeFiles/Version_Convolutionnal.dir/depend:
	cd /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug /home/cheerfulliu/Desktop/CNN_MANUSCRIPT_ZHIYUAN/CNN_Manuscript/cmake-build-debug/CMakeFiles/Version_Convolutionnal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Version_Convolutionnal.dir/depend

