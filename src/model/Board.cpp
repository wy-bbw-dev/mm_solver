//
// Created by ich on 3/27/23.
//

#include <model/Board.h>
#include <cassert>

Board::Board(Position maxWidth, Position maxHeight) : maxWidth(maxWidth), maxHeight(maxHeight) {}

void Board::place_meeple(Meeple meeple, Coordinate coordinate) {

    if (auto current_location = meeple_positions.find(meeple); current_location != meeple_positions.end()) {
        m_meeples_in_row[current_location->second.first].erase(meeple);
        m_meeples_in_column[current_location->second.second].erase(meeple);
    }
    meeple_positions[meeple] = coordinate;
    m_meeples_in_row[coordinate.first].insert(meeple);
    m_meeples_in_column[coordinate.second].insert(meeple);
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