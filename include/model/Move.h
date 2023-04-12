//
// Created by ich on 3/27/23.
//

#pragma once

#include <cstdint>
#include <ostream>
#include <vector>
#include "typedefs.h"
#include "Meeple.h"

struct Move {
    Coordinate to;
    auto operator<=>(const Move&) const = default;
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};

using MoveCollection = std::vector<Move>;
