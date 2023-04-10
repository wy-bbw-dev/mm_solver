//
// Created by ich on 4/10/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <model/Board.h>
#include <model/Move.h>
#include <algorithm>

TEST_CASE("Move options on a  free board", "[Move]") {
    Board board(3, 3);
    board.place_meeple(Meeple::OZZY_MOSIS, {1, 1});

    auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
    SECTION("Move up") {
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{0, 1}}));
    }

    SECTION("Move down") {
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{2, 1}}));
    }

    SECTION("Move left") {
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{1, 0}}));
    }

    SECTION("Move right") {
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{1, 2}}));
    }

    board.place_meeple(Meeple::OZZY_MOSIS, {0, 1});
    moves = possible_moves(board, Meeple::OZZY_MOSIS);

    SECTION ("Move up is not possible") {
        REQUIRE_THAT(moves, !Catch::Matchers::VectorContains(Move{{0, 1}}));
    }
}

TEST_CASE("Move options when blocked by another meeple", "[Move]") {
    Board board(3, 3);
    board.place_meeple(Meeple::OZZY_MOSIS, {1, 1});
    board.place_meeple(Meeple::BLUE_BEAMER, {0, 1});

    Coordinate coordinates[] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    for (auto coordinate : coordinates) {
        board.place_meeple(Meeple::BLUE_BEAMER, coordinate);
        auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(3 == moves.size());
        REQUIRE_THAT(moves, !Catch::Matchers::VectorContains(Move{coordinate}));
    }
}