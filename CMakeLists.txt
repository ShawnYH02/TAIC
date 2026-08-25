cmake_minimum_required(VERSION 3.30)
project(TAIC)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAIC main.cpp
        include/ir/DType.h
        include/ir/TensorType.h
        include/ir/Value.h
        include/ir/Operation.h
        include/ir/Graph.h
        src/ir/Verifier.cpp
        src/ir/Printer.cpp
        tests/test_ir.cpp
        src/ir/TensorType.cpp
        src/ir/Value.cpp
        src/ir/Operation.cpp
        src/ir/Graph.cpp
        include/ir/Printer.h)

target_include_directories(TAIC PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)