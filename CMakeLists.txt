cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp DynamicArray.hpp LinkedList.hpp ListSequence.hpp Sequence.h Sequence.cpp ArraySequence.hpp
        Errors.h LinkedListTests.hpp ListSequenceTests.hpp DynamicArrayTests.hpp ArraySequenceTests.hpp)
