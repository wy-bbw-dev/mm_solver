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

struct ColumnBlocks{
    const std::optional<Position> top;
    const std::optional<Position> bottom;
};

struct RowBlocks {
    const std::optional<Position> left;
    const std::optional<Position> right;
};

template<>
struct std::hash<Coordinate> {
    std::size_t operator()(const Coordinate &coordinate) const {
        return std::hash<Position>()(coordinate.first) ^ std::hash<Position>()(coordinate.second);
    }
};


class Board {
public:
    Board(Position maxWidth, Position maxHeight);
    ~Board() = default;
    Board(const Board& other) = default;
    Board(Board&& other) noexcept = default;
    Board& operator=(const Board& other) = default;
    Board& operator=(Board&& other) noexcept = default;

    void place_meeple(Meeple meeple, Coordinate coordinate);

    void add_blocking_floor(Position row, Position col);
    void add_blocking_wall(Position row, Position col);
    void add_teleport(Coordinate coordinate);
    void set_destination(Coordinate coordinate);
    Coordinate destination() const;

    Coordinate meeple_location(const Meeple& meeple) const;
    const CoordinateCollection& teleport_locations() const;
    PositionCollection floors(const Position& column) const;
    PositionCollection walls(const Position& row) const;
    Position width() const;
    Position height() const;

    RowBlocks blocked_by_meeple_in_row(const Coordinate& coord) const;
    ColumnBlocks blocked_by_meeple_in_column(const Coordinate& coord) const;
    ColumnBlocks blocks_by_floor(const Coordinate& coord) const;
    RowBlocks blocks_by_wall(const Coordinate& coord) const;

private:
    std::unordered_map<Meeple, Coordinate > meeple_positions;
    std::unordered_multimap<Position, Meeple> m_meeples_in_row;
    std::unordered_multimap<Position, Meeple> m_meeples_in_column;

    std::unordered_multimap<Position, Position> m_floor_blocks;
    std::unordered_multimap<Position, Position> m_wall_blocks;
    CoordinateCollection teleport;
    Coordinate m_destination;
    Position maxWidth;
    Position maxHeight;
};