//
// Created by ich on 4/15/23.
//

#pragma once

#include <model/Move.h>
#include <model/Board.h>


MoveCollection possible_moves(const Board& board, const Meeple& meeple);

template<Meeple meeple>
MoveCollection possible_special_moves(const Board& board);