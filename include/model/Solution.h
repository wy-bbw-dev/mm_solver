//
// Created by ich on 4/15/23.
//

#pragma once

#include <list>
#include <array>

#include <model/Meeple.h>
#include <model/Move.h>

struct Solution {
    std::array<std::pair<Meeple, std::list<Move>>, 3> moves_by_meeple;
    bool success = false;
};