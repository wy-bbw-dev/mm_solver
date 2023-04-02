//
// Created by ich on 3/27/23.
//

#pragma once

#include <cstdint>
#include "typedefs.h"
#include "Meeple.h"
#include "Board.h"

struct Move;
using MoveCollection = std::vector<Move>;

struct Move {
    Coordinate to;
    bool special;
};

MoveCollection possible_moves(const Board& board, const Meeple& meeple);

template<Meeple meeple>
MoveCollection possible_special_moves(const Board& board);