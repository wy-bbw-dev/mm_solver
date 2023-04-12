//
// Created by ich on 4/15/23.
//

#include <catch2/catch_test_macros.hpp>
#include "model/Board.h"
#include <controller/BacktrackingController.h>
#include <controller/SolutionActions.h>

TEST_CASE("Solver handles an empty board", "[Solver]") {
    SECTION("Meeple starts on target position") {
        Board board(2, 2);
        board.set_destination({0, 0});
        board.place_meeple(Meeple::OZZY_MOSIS, {0, 0});

        BacktrackingController controller( {Meeple::OZZY_MOSIS});
        Solution solution = controller.solve(board);

        solution::apply(solution, board);
        REQUIRE(board.meeple_location(Meeple::OZZY_MOSIS) == board.destination());
    }
}