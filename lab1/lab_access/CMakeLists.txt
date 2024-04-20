cmake_minimum_required(VERSION 3.9)



project(lab1)

find_package(MPI REQUIRED)
link_libraries(MPI::MPI_CXX)

add_definitions(-DOMPI_SKIP_MPICXX)
add_executable(pi pi.cpp)
add_executable(pi_ pi_.cpp)
add_executable(msg msg.cpp)


