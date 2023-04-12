//
// Created by ich on 4/15/23.
//

#include <model/MoveComputations.h>

auto MAX_UNION(std::optional<Position> a, std::optional<Position> b) -> std::optional<Position> {
    if (a.has_value() && b.has_value()) {
        return std::max(a.value(), b.value());
    } else if (a.has_value()) {
        return a.value();
    } else if (b.has_value()) {
        return b.value();
    } else {
        return std::optional<Position>();
    }
}

auto MIN_UNION(std::optional<Position> a, std::optional<Position> b) -> std::optional<Position> {
    if (a.has_value() && b.has_value()) {
        return std::min(a.value(), b.value());
    } else if (a.has_value()) {
        return a.value();
    } else if (b.has_value()) {
        return b.value();
    } else {
        return std::optional<Position>();
    }
}

ColumnBlocks column_block_intersection(const ColumnBlocks& a, const ColumnBlocks& b) {
    return {MAX_UNION(a.top, b.top), MIN_UNION(a.bottom, b.bottom)};
}

RowBlocks row_block_intersection(const RowBlocks& a, const RowBlocks& b) {
    return {MAX_UNION(a.left, b.left), MIN_UNION(a.right, b.right)};
}

MoveCollection possible_moves(const Board& board, const Meeple& meeple) {
    MoveCollection moves;
    auto [row, col] = board.meeple_location(meeple);

    ColumnBlocks column_blocks_by_meeple = board.blocked_by_meeple_in_column({row, col});
    ColumnBlocks column_blocks_by_wall = board.blocks_by_floor({row, col});
    ColumnBlocks column_blocks = column_block_intersection(column_blocks_by_meeple, column_blocks_by_wall);

    if (column_blocks.top.has_value()) {
        if (column_blocks.top.value() + 1 < row) {
            moves.push_back(Move{{column_blocks.top.value() + 1, col}});
        }
    } else {
        if (row > 0) {
            moves.push_back(Move{{0, col}});
        }
    }
    if (column_blocks.bottom.has_value()) {
        if (column_blocks.bottom.value() - 1> row) {
            moves.push_back(Move{{column_blocks.bottom.value() - 1, col}});
        }
    } else {
        if (row < board.height() - 1) {
            moves.push_back(Move{{board.height() - 1, col}});
        }
    }


    RowBlocks row_blocks_by_meeple = board.blocked_by_meeple_in_row({row, col});
    RowBlocks row_blocks_by_wall = board.blocks_by_wall({row, col});
    RowBlocks row_blocks = row_block_intersection(row_blocks_by_meeple, row_blocks_by_wall);

    if (row_blocks.left.has_value()) {
        if (row_blocks.left.value() + 1 < col) {
            moves.push_back(Move{{row, row_blocks.left.value() + 1}});
        }
    } else {
        if (col > 0) {
            moves.push_back(Move{{row, 0}});
        }
    }
    if (row_blocks.right.has_value()) {
        if (row_blocks.right.value() - 1 > col) {
            moves.push_back(Move{{row, row_blocks.right.value() - 1}});
        }
    } else {
        if (col < board.width() - 1) {
            moves.push_back(Move{{row, board.width() - 1}});
        }
    }

    return moves;
}