//
// Created by ich on 3/27/23.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <model/Board.h>
#include "view/ascii/BoardPrinter.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>

TEST_CASE("empty board should have a frame and letters", "[BoardPrinterTest]") {
//    auto console = spdlog::stdout_color_mt("console");
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
}

TEST_CASE("board with one meeple should have a frame and letters and a meeple", "[BoardPrinterTest]") {
    Board board(1,1);
    board.placeMeeple(Meeple::BLUE_BEAMER, Coordinate(0,0));
    auto board_string = ascii::print(board);
    SECTION("third line should have a meeple") {
        REQUIRE(board_string[12] == '2');
    }

    SECTION("meeple should override teleport") {
        board.addTeleport({0,0});
        board_string = ascii::print(board);
        REQUIRE(board_string[12] == '2');
    }
}

TEST_CASE("board a teleport should have a T at (0,0)", "[BoardPrinterTest]") {
    Board board(1,1);
    board.addTeleport({0,0});
    auto board_string = ascii::print(board);
    SECTION("third line should have a T") {
        REQUIRE(board_string[12] == 'T');
    }
}

TEST_CASE("board with a horizontal barrier should have a frame and letters and the barrier", "[BoardPrinterTest]") {
    Board board(2,2);
    board.addHorizontalBarrier(0,0);
    auto board_string = ascii::print(board);
    REQUIRE(board_string.size() == 42);
    REQUIRE(board_string[2] == 'A');
    REQUIRE(board_string[4] == 'B');
    SECTION("second row line should have a barrier") {
        REQUIRE(board_string[17] == '|');
    }
}

TEST_CASE("board with a vertical should have frame and letters and the barrier", "[BoardPrinterTest") {
    Board board(2,2);
    board.addVerticalBarrier(0,0);
    auto board_string = ascii::print(board);
    REQUIRE(board_string.size() == 42);

    SECTION("second row line should have a barrier") {
        REQUIRE(board_string[23] == '-');
    }
}