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
    BacktrackingController(std::vector<Meeple> availableMeeples);
    Solution solve(Board board);
private:
    std::vector<Meeple> availableMeeples;
};