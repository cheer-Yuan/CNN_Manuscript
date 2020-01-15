cmake_minimum_required(VERSION 3.15)
project(Version_Convolutionnal C)

set(CMAKE_C_STANDARD 11)

add_executable(Version_Convolutionnal main.c rgb2Grayscale.h data_Images.h cnn.c cnn.h data_Images.c mat.c mat.h label_Writer.cpp test.c)

target_link_libraries(Version_Convolutionnal m)