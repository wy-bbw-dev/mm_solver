add_executable(BoardTest)

target_sources(BoardTest PRIVATE
    BoardTest.cpp
)

target_link_libraries(BoardTest PRIVATE
        mm_solver_lib
        Catch2::Catch2WithMain
        )

add_test(NAME BoardTest
        COMMAND BoardTest
        )