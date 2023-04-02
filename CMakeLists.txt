cmake_minimum_required(VERSION 3.26)
project(mm_solver)

set(CMAKE_CXX_STANDARD 20)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/_conan)
execute_process(
        COMMAND conan install ${CMAKE_CURRENT_SOURCE_DIR} --build=missing -s build_type=Debug -of ${CMAKE_BINARY_DIR}/_conan
        COMMAND_ERROR_IS_FATAL ANY
        )

find_package(fmt REQUIRED HINTS ${CMAKE_BINARY_DIR}/_conan)
find_package(Catch2 REQUIRED HINTS ${CMAKE_BINARY_DIR}/_conan)
find_package(spdlog REQUIRED HINTS ${CMAKE_BINARY_DIR}/_conan)


add_library(mm_solver_lib OBJECT)
target_sources(mm_solver_lib PRIVATE
        src/model/Board.cpp
        src/model/Move.cpp
        src/view/ascii/BoardPrinter.cpp
        )

target_link_libraries(mm_solver_lib PUBLIC
        spdlog::spdlog
        )


add_executable(mm_solver)

target_sources(mm_solver PRIVATE
        src/main.cpp
        )

target_include_directories(mm_solver_lib PUBLIC
        include)

target_link_libraries(mm_solver PRIVATE
        mm_solver_lib
        )

enable_testing()
add_subdirectory(test)
