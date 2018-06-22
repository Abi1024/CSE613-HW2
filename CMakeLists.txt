cmake_minimum_required(VERSION 3.10)
project(hw2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11 -fopenmp")

include_directories(.)

add_executable(hw2
    check_sorted.cpp
    check_sorted.h
    error.cpp
    error.h
    main.cpp
    mst.cpp
    mst.h
    prefix_sum.cpp
    prefix_sum.h
    quicksort.cpp
    quicksort.h
    radixsort.cpp
    radixsort.h
    random.cpp
    random.h)
