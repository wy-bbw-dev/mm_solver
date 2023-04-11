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

    SECTION("Placed in the top left corner, there should be 2 moves") {
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});
        moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(2 == moves.size());
        REQUIRE(std::find(moves.begin(), moves.end(), Move{{0, 2}}) != moves.end());
        REQUIRE(std::find(moves.begin(), moves.end(), Move{{2, 0}}) != moves.end());
    }

    SECTION("Placed in the bottom right corner, there should be 2 moves") {
        board.place_meeple(Meeple::OZZY_MOSIS, {2, 2});
        moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(2 == moves.size());
        REQUIRE(std::find(moves.begin(), moves.end(), Move{{0, 2}}) != moves.end());
        REQUIRE(std::find(moves.begin(), moves.end(), Move{{2, 0}}) != moves.end());
    }
}

TEST_CASE("Move options when blocked by another meeple", "[Move]") {
    Board board(3, 3);

    SECTION("A meeple in the center with a neighbouring meeple should not be able to move into that position") {
        board.place_meeple(Meeple::OZZY_MOSIS, {1, 1});
        board.place_meeple(Meeple::BLUE_BEAMER, {0, 1});

        Coordinate coordinates[] = {{0, 1},
                                    {1, 0},
                                    {1, 2},
                                    {2, 1}};

        for (auto coordinate: coordinates) {
            board.place_meeple(Meeple::BLUE_BEAMER, coordinate);
            auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
            REQUIRE(3 == moves.size());
            REQUIRE_THAT(moves, !Catch::Matchers::VectorContains(Move{coordinate}));
        }
    }

    SECTION("A meeple in a corner with blocked by another meeple has only one direction to move") {
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});
        board.place_meeple(Meeple::BLUE_BEAMER, {0, 1});


        auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(1 == moves.size());
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{2, 0}}));
    }

    SECTION("Placing the blocking meeple multiple times in several locations should not impact the current move options") {
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});
        board.place_meeple(Meeple::BLUE_BEAMER, {0, 1});
        board.place_meeple(Meeple::BLUE_BEAMER, {1, 0});
        board.place_meeple(Meeple::BLUE_BEAMER, {1, 2});
        board.place_meeple(Meeple::BLUE_BEAMER, {2, 1});
        board.place_meeple(Meeple::BLUE_BEAMER, {0, 1});

        auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(1 == moves.size());
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{2, 0}}));
    }

    SECTION("On a larger board, the meeple can move up to the field before another meeple") {
        Board board(5, 5);
        board.place_meeple(Meeple::OZZY_MOSIS, {1, 1});
        board.place_meeple(Meeple::BLUE_BEAMER, {1, 4});
        board.place_meeple(Meeple::CARBON, {4, 1});


        auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(4 == moves.size());
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{0, 1}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{1, 0}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{3, 1}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{1, 3}}));
    }

    SECTION("Symmetry is a given. I.e. the direction of blockage does not matter on large boards either") {
        Board board(5, 5);
        board.place_meeple(Meeple::OZZY_MOSIS, {3, 3});
        board.place_meeple(Meeple::BLUE_BEAMER, {0, 3});
        board.place_meeple(Meeple::CARBON, {3, 0});

        auto moves = possible_moves(board, Meeple::OZZY_MOSIS);
        REQUIRE(4 == moves.size());
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{1, 3}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{3, 1}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{4, 3}}));
        REQUIRE_THAT(moves, Catch::Matchers::VectorContains(Move{{3, 4}}));
    }
}