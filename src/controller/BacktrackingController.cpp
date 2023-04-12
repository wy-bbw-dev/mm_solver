//
// Created by ich on 4/15/23.
//

#include <controller/BacktrackingController.h>

BacktrackingController::BacktrackingController( std::vector<Meeple> meeples) :  availableMeeples(meeples) {}

Solution BacktrackingController::solve(Board board) {
    return Solution();
}