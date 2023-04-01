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
#include "Meeple.h"
#include "typedefs.h"



using BarrierPosition = std::pair<Position, Position>;
using CoordinateCollection = std::vector<Coordinate>;
using PositionCollection = std::vector<Position>;

template<>
struct std::hash<Coordinate> {
    std::size_t operator()(const Coordinate &coordinate) const {
        return std::hash<Position>()(coordinate.first) ^ std::hash<Position>()(coordinate.second);
    }
};


class Board {
public:
    Board(Position maxWidth, Position maxHeight);

    void placeMeeple(Meeple meeple, Coordinate coordinate);
    void addHorizontalBarrier(Position x, Position y);
    void addVerticalBarrier(Position x, Position y);
    void addTeleport(Coordinate coordinate);

    Coordinate meepleLocation(const Meeple& meeple) const;
    const CoordinateCollection& teleportLocations() const;
    PositionCollection horizontalStops(const Position& position) const;
    PositionCollection verticalStops(const Position& position) const;
    Position width() const;
    Position height() const;

private:
    std::unordered_map<Meeple, Coordinate > meeplePositions;
    std::unordered_multimap<Position, BarrierPosition> horizontalBarriers;
    std::unordered_multimap<Position, BarrierPosition> verticalBarriers;
    CoordinateCollection teleport;
    Coordinate destination;
    Position maxWidth;
    Position maxHeight;
};