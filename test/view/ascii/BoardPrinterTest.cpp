//
// Created by ich on 3/27/23.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <model/Board.h>
#include "view/ascii/BoardPrinter.h"

TEST_CASE("empty board should have a frame and letters", "[BoardPrinterTest]") {
    Board board(1,1);
    auto board_string = ascii::print(board);
    SECTION("each line should be 5 characters long and end with a line break") {
        REQUIRE(board_string[4]  == '\n');
        REQUIRE(board_string[9]  == '\n');
        REQUIRE(board_string[14]  == '\n');
        REQUIRE(board_string[19]  == '\n');
    }

    SECTION("first line should have a letter for the board column. Third line should have a letter for the board row") {
        REQUIRE(board_string[0]  == ' ');
        REQUIRE(board_string[2]  == 'A');
        REQUIRE(board_string[10]  == 'A');
    }

    SECTION("second line should have a frame") {
        REQUIRE(board_string[6] == '|');
        REQUIRE(board_string[7] == '-');
        REQUIRE(board_string[8] == '|');
    }

    SECTION("third line should have a frame and a space") {
        REQUIRE(board_string[11] == '|');
        REQUIRE(board_string[12] == ' ');
        REQUIRE(board_string[13] == '|');
    }

    SECTION("fourth line should have a frame") {
        REQUIRE(board_string[16] == '|');
        REQUIRE(board_string[17] == '-');
        REQUIRE(board_string[18] == '|');
    }

//    REQUIRE(board_string == "  A \n |-|\nA| |\n |-|\n");
}