//
// Created by ich on 3/27/23.
//
#pragma once

#include <utility>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <unordered_set>
#include <vector>
#include <set>
#include <optional>
#include "Meeple.h"
#include "typedefs.h"



using CoordinateCollection = std::vector<Coordinate>;
using PositionCollection = std::vector<Position>;
using MeepleSet = std::set<Meeple>;

template<>
struct std::hash<Coordinate> {
    std::size_t operator()(const Coordinate &coordinate) const {
        return std::hash<Position>()(coordinate.first) ^ std::hash<Position>()(coordinate.second);
    }
};


class Board {
public:
    Board(Position maxWidth, Position maxHeight);

    void place_meeple(Meeple meeple, Coordinate coordinate);

    void add_horizontal_barrier(Position x, Position y);
    void add_vertical_barrier(Position x, Position y);
    void add_teleport(Coordinate coordinate);

    Coordinate meeple_location(const Meeple& meeple) const;
    const CoordinateCollection& teleport_locations() const;
    PositionCollection horizontal_barriers(const Position& position) const;
    PositionCollection vertical_barriers(const Position& position) const;
    Position width() const;
    Position height() const;

    MeepleSet* meeples_in_row(const Position& position) const;
    MeepleSet* meeples_in_column(const Position& position) const;

private:
    std::unordered_map<Meeple, Coordinate > meeple_positions;
    std::unordered_map<Position, std::set<Meeple> > m_meeples_in_row;
    std::unordered_map<Position, std::set<Meeple> > m_meeples_in_column;

    std::unordered_multimap<Position, Position> m_horizontal_barriers;
    std::unordered_multimap<Position, Position> m_vertical_barriers;
    CoordinateCollection teleport;
    Coordinate destination;
    Position maxWidth;
    Position maxHeight;
};