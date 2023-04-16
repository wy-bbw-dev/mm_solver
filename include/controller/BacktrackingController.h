//
// Created by ich on 3/27/23.
//

#pragma once

#include <vector>
#include "model/Meeple.h"
#include "model/Solution.h"
#include "model/Board.h"

class BacktrackingController {
public:
    BacktrackingController(const std::vector<Meeple>& availableMeeples);
    Solution solve(Board board);
    void run_backtracking_for_meeple(Board& board, Solution& solution, std::set<Meeple> usedMeeples);
private:
    std::set<Meeple> availableMeeples;
};