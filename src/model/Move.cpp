//
// Created by ich on 4/2/23.
//
#include <algorithm>
#include <model/Move.h>


MoveCollection possible_moves(const Board& board, const Meeple& meeple) {
    MoveCollection moves;
    auto [row, col] = board.meeple_location(meeple);

    ColumnBlocks column_blocks_by_meeple = board.blocked_by_meeple_in_column({row, col});

    if (column_blocks_by_meeple.top.has_value()) {
        if (column_blocks_by_meeple.top.value() + 1 < row) {
            moves.push_back(Move{{column_blocks_by_meeple.top.value() + 1, col}});
        }
    } else {
        if (row > 0) {
            moves.push_back(Move{{0, col}});
        }
    }
    if (column_blocks_by_meeple.bottom.has_value()) {
        if (column_blocks_by_meeple.bottom.value() - 1> row) {
            moves.push_back(Move{{column_blocks_by_meeple.bottom.value() - 1, col}});
        }
    } else {
        if (row < board.height() - 1) {
            moves.push_back(Move{{board.height() - 1, col}});
        }
    }


    RowBlocks row_blocks_by_meeple = board.blocked_by_meeple_in_row({row, col});
    if (row_blocks_by_meeple.left.has_value()) {
        if (row_blocks_by_meeple.left.value() + 1 < col) {
            moves.push_back(Move{{row, row_blocks_by_meeple.left.value() + 1}});
        }
    } else {
        if (col > 0) {
            moves.push_back(Move{{row, 0}});
        }
    }
    if (row_blocks_by_meeple.right.has_value()) {
        if (row_blocks_by_meeple.right.value() - 1 > col) {
            moves.push_back(Move{{row, row_blocks_by_meeple.right.value() - 1}});
        }
    } else {
        if (col < board.width() - 1) {
            moves.push_back(Move{{row, board.width() - 1}});
        }
    }

    return moves;
}

template<typename T>
std::ostream &operator<<(std::ostream& os, const std::pair<T, T>& t) {
    os << t.first << ", " << t.second;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << "Move{" << move.to << "}";
    return os;
}