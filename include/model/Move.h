//
// Created by ich on 3/27/23.
//

#pragma once

#include <cstdint>
#include <ostream>
#include "typedefs.h"
#include "Meeple.h"
#include "Board.h"

struct Move;
using MoveCollection = std::vector<Move>;

struct Move {
    Coordinate to;
    auto operator<=>(const Move&) const = default;
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
};

MoveCollection possible_moves(const Board& board, const Meeple& meeple);

template<Meeple meeple>
MoveCollection possible_special_moves(const Board& board);