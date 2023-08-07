
project(main)

######## A simple cmakelists.txt file for OpenCV() #############  
#cmake_minimum_required(VERSION 3.26)  
cmake_minimum_required(VERSION 3.17)
#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

add_executable(main main.cpp)

find_package(MPI REQUIRED)
if (MPI_FOUND)
    MESSAGE("{MPI_CXX_LIBRARIES}")
    else (MPI_FOUND)
    MESSAGE (SEND_ERROR "This application cannot compile without MPI")
endif(MPI_FOUND)



include_directories(SYSTEM ${MPI_INCLUDES_PATH})
target_include_directories(main PUBLIC ${MPI_CXX_INCLUDE_DIRS})
target_link_libraries(main PUBLIC ${MPI_CXX_LIBRARIES} )

########### end ####################################  