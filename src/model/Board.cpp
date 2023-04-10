//
// Created by ich on 3/27/23.
//

#include <model/Board.h>
#include <cassert>
#include <algorithm>

Board::Board(Position maxWidth, Position maxHeight) : maxWidth(maxWidth), maxHeight(maxHeight) {}

void Board::place_meeple(Meeple meeple, Coordinate coordinate) {
    auto [row, col] = coordinate;
    if (auto current_location = meeple_positions.find(meeple); current_location != meeple_positions.end()) {
        auto [current_row, current_col] = current_location->second;
        auto [row_begin, row_end] = m_meeples_in_row.equal_range({current_row});
        for (auto it = row_begin; it != row_end; ++it) {
            if (it->second == meeple) {
                m_meeples_in_row.erase(it);
                break;
            }
        }

        auto [col_begin, col_end] = m_meeples_in_column.equal_range({current_col});
        for (auto it = col_begin; it != col_end; ++it) {
            if (it->second == meeple) {
                m_meeples_in_column.erase(it);
                break;
            }
        }
    }
    meeple_positions[meeple] = coordinate;
    m_meeples_in_row.insert({row, meeple});
    m_meeples_in_column.insert({col, meeple});
    return;
}

void Board::add_horizontal_barrier(Position x, Position y) {
    auto inserted_at = m_horizontal_barriers.insert({x, y });
    assert(inserted_at != m_horizontal_barriers.end());
}

void Board::add_vertical_barrier(Position x, Position y) {
    auto inserted_at = m_vertical_barriers.insert({y, x});
    assert(inserted_at != m_vertical_barriers.end());
}

void Board::add_teleport(Coordinate coordinate) {
    teleport.push_back(coordinate);
}

Coordinate Board::meeple_location(const Meeple& meeple) const {
    return meeple_positions.at(meeple);
}

const CoordinateCollection&  Board::teleport_locations() const {
    return teleport;
}

ColumnBlocks Board::blocked_by_meeple_in_column(const Coordinate& coord) const {
    auto [row, col] = coord;
    auto [meeples_begin, meeples_end] = m_meeples_in_column.equal_range(col);
    std::optional<Position> blocked_up, blocked_down;
    for (auto it = meeples_begin; it != meeples_end; ++it) {
        auto [block_row, block_col] = meeple_positions.at(it->second);
        if (block_row < row) {
            if (blocked_up.has_value()) {
                blocked_up = std::max(blocked_up.value(), block_row);
            } else {
                blocked_up = block_row;
            }
        }

        if (block_row > row) {
            if (blocked_down.has_value()) {
                blocked_down = std::min(blocked_down.value(), block_row);
            } else {
                blocked_down = block_row;
            }
        }
    }
    return {blocked_up, blocked_down};
}

RowBlocks Board::blocked_by_meeple_in_row(const Coordinate& coord) const {
    auto [row, col] = coord;
    auto [meeples_begin, meeples_end] = m_meeples_in_row.equal_range(row);
    std::optional<Position> blocked_left, blocked_right;
    for (auto it = meeples_begin; it != meeples_end; ++it) {
        auto [block_row, block_col] = meeple_positions.at(it->second);
        if (block_col < col) {
            if (blocked_left.has_value()) {
                blocked_left = std::max(blocked_left.value(), block_col);
            } else {
                blocked_left = block_col;
            }
        }

        if (block_col > col) {
            if (blocked_right.has_value()) {
                blocked_right = std::min(blocked_right.value(), block_col);
            } else {
                blocked_right = block_col;
            }
        }
    }
    return {blocked_left, blocked_right};
}

PositionCollection Board::horizontal_barriers(const Position& position) const {
    PositionCollection stops;
    auto [begin, end] = m_horizontal_barriers.equal_range(position);
    for (auto it = begin; it != end; ++it) {
        stops.push_back(it->second);
    }
    return stops;
}

PositionCollection Board::vertical_barriers(const Position &position) const {
    PositionCollection stops;
    auto [begin, end] = m_vertical_barriers.equal_range(position);
    for (auto it = begin; it != end; ++it) {
        stops.push_back(it->second);
    }
    return stops;
}

Position Board::width() const {
    return maxWidth;
}

Position Board::height() const {
    return maxHeight;
}