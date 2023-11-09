# Define executable target and its sources
#lib cmake
cmake_minimum_required(VERSION 3.2)


#Source files
set(SRC_FILES DIO_program.c PORT_program.c)


#setting CMake wont run on nativ machine (cross compiler)
set(CMAKE_SYSTEM_NAME Generic)
#Setting Compiler 
set(CMAKE_C_COMPILER avr-gcc)
#Name of Static Library
set(LibName DIO)

####################################################################################

project(libDIO.a C)

#Create a static library .a from .c files
add_library(${LibName} STATIC ${SRC_FILES})

#include the inc direct.
target_include_directories(${LibName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc/)

















# set(CMAKE_C_FLAGS "-c")
#add_executable(ObjFiles main.c can.c uart.c)
#target_link_libraries(PORT_program.o PRIVATE libDIO.a)