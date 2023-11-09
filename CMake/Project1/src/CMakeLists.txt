# Define executable target and its sources
#exe cmake
cmake_minimum_required(VERSION 3.2)

#setting main variables
#MCU
set(MCU atmega32)
#Optimization level
set(OPTIM_LVL 1)
#Source files
set(SRC_FILES main.c)
set(SRC_FILES2 ../lib/DIO_program.c ../lib/PORT_program.c)


#setting CMake wont run on nativ machine (cross compiler)
set(CMAKE_SYSTEM_NAME Generic)
#Setting Compiler 
set(CMAKE_C_COMPILER avr-gcc)
#Generate the .hex file
set(CMAKE_OBJCOPY avr-objcopy)
#Setting Flags
set(CMAKE_C_FLAGS "-O${OPTIM_LVL} -mmcu=${MCU}")
#name of op file
set(OutPUT Snake)
#Tool to generate the info about the the hex file
set(FileINFO avr-size)
#Name of report file
set(ReportName binaryReport)
#Name of Static Library
set(LibName DIO)

######################################################################################


project(SnakeEffect)


# Create binary
add_executable(${OutPUT}.elf ${SRC_FILES})

target_include_directories(${OutPUT}.elf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc/)


add_library(${LibName} STATIC ${SRC_FILES2})

# Link the Binary with the Static lib
target_link_libraries(${OutPUT}.elf PUBLIC ${LibName})


add_custom_target(Create_Hex_AND_Report ALL
                  DEPENDS ${OutPUT}.elf
                  COMMAND ${CMAKE_OBJCOPY} -O ihex ${OutPUT}.elf ${OutPUT}.hex
                  COMMAND ${FileINFO} ${OutPUT}.elf > ${ReportName}.txt)   
