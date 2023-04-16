//
// Created by ich on 4/15/23.
//

#include <controller/BacktrackingController.h>

// TODO: accept two iterators instead of a vector
BacktrackingController::BacktrackingController(const std::vector<Meeple>& meeples) :  availableMeeples(meeples.begin(), meeples.end()) {}

Solution BacktrackingController::solve(Board board) {
    Solution solution;
    run_backtracking_for_meeple(board, solution, {});
    return Solution();
}

void
BacktrackingController::run_backtracking_for_meeple(Board &board, Solution &solution, std::set<Meeple> usedMeeples) {

}