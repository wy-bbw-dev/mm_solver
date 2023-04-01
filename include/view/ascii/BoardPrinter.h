//
// Created by ich on 3/27/23.
//

#pragma once
#include <string>
#include "model/Board.h"

namespace ascii {
    using BoardString = std::string;
    BoardString print(const Board& board);
}