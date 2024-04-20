cmake_minimum_required(VERSION 3.9)



project(lab1)

find_package(MPI REQUIRED)

add_definitions(-DOMPI_SKIP_MPICXX)
add_executable(pi pi.cpp)
add_executable(msg msg.cpp)

target_link_libraries(pi PUBLIC MPI::MPI_CXX)
target_link_libraries(msg PUBLIC MPI::MPI_CXX)