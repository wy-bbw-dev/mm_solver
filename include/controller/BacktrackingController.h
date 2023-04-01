//
// Created by ich on 3/27/23.
//

#pragma once

#include <vector>
#include "model/Meeple.h"

class BacktrackingController {
public:
    BacktrackingController(std::vector<Meeple> availableMeeples);
    void solve();
private:
    std::vector<Meeple> availableMeeples;
};