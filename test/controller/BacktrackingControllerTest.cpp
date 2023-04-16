//
// Created by ich on 4/15/23.
//

#include <catch2/catch_test_macros.hpp>
#include "model/Board.h"
#include <controller/BacktrackingController.h>
#include <controller/SolutionActions.h>


std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate) {
    os << "{" << coordinate.first << ", " << coordinate.second << "}";
    return os;
}

TEST_CASE("Solver handles an empty board", "[Solver]") {
    SECTION("Meeple starts on target position") {
        Board board(2, 2);
        board.set_destination({0, 0});
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});

        BacktrackingController controller( {Meeple::OZZY_MOSIS});
        Solution solution = controller.solve(board);

        solution::apply(solution, board);
        REQUIRE(solution.success);
        REQUIRE(board.meeple_location(Meeple::OZZY_MOSIS) == board.destination());
    }

    SECTION("Meeple needs a single move to reach target position") {
        Board board(2, 2);
        board.set_destination({1, 0});
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});

        BacktrackingController controller( {Meeple::OZZY_MOSIS});
        Solution solution = controller.solve(board);

        solution::apply(solution, board);
        REQUIRE(solution.success);

        Coordinate meeple_location = board.meeple_location(Meeple::OZZY_MOSIS);
        Coordinate target_location = board.destination();

        REQUIRE(meeple_location == target_location);
    }
}