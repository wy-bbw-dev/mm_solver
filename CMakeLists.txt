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

option(ENABLE_COVERAGE "enable coverage" OFF)
if (ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
    add_custom_target(init
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND rm -f ${OBJECT_DIR}/*.gcno
        COMMAND rm -f ${OBJECT_DIR}/*.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

option(USE_ASAN "enable address sanitizer" OFF)
if (USE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -fPIC)
    add_link_options(-fsanitize=address)
endif()

option(USE_UBSAN "enable undefined behavior sanitizer" OFF)
if (USE_UBSAN)
    add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer -fPIC)
    add_link_options(-fsanitize=undefined)
endif()



add_library(mm_solver_lib OBJECT)
target_sources(mm_solver_lib PRIVATE
        src/model/Board.cpp
        src/model/Move.cpp
        src/model/MoveComputations.cpp
        src/view/ascii/BoardPrinter.cpp
        src/controller/BacktrackingController.cpp
        src/controller/SolutionActions.cpp
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
