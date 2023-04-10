//
// Created by ich on 4/2/23.
//

#include <catch2/catch_test_macros.hpp>
#include <model/Board.h>

TEST_CASE("Board is initialized with correct size", "[Board]") {
    Board board(2, 2);
    REQUIRE(board.width() == 2);
    REQUIRE(board.height() == 2);
}