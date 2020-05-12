cmake_minimum_required(VERSION 3.15)
project(Version_Convolutionnal C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


add_executable(Version_Convolutionnal main.c rgb2Grayscale.h data_Images.h data_Images.c mat.c mat.h label_Writer.cpp cnn_1.c cnn_1.h)

target_link_libraries(Version_Convolutionnal m)