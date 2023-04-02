
add_executable(BoardPrinterTest)
target_link_libraries(BoardPrinterTest Catch2::Catch2WithMain mm_solver_lib)
target_sources(BoardPrinterTest PRIVATE
        BoardPrinterTest.cpp
        )

add_test(NAME BoardPrinterTest
        COMMAND BoardPrinterTest)