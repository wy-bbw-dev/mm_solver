//
// Created by ich on 3/27/23.
//

#include <model/Board.h>
#include <cassert>

Board::Board(Position maxWidth, Position maxHeight) {
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
}

void Board::placeMeeple(Meeple meeple, Coordinate coordinate) {
    auto success = meeplePositions.insert({meeple, coordinate});
    assert(success.second);
}

void Board::addHorizontalBarrier(Position x, Position y) {
    auto inserted_at = horizontalBarriers.insert({x, {y, y + 1}});
    assert(inserted_at != horizontalBarriers.end());
}

void Board::addVerticalBarrier(Position x, Position y) {
    auto inserted_at = verticalBarriers.insert({y, {x, x + 1}});
    assert(inserted_at != verticalBarriers.end());
}

void Board::addTeleport(Coordinate coordinate) {
    teleport.push_back(coordinate);
}

Coordinate Board::meepleLocation(const Meeple& meeple) const {
    return meeplePositions.at(meeple);
}

const CoordinateCollection&  Board::teleportLocations() const {
    return teleport;
}

PositionCollection Board::horizontalStops(const Position& position) const {
    PositionCollection stops;
    auto range = horizontalBarriers.equal_range(position);
    for (auto it = range.first; it != range.second; ++it) {
        stops.push_back(it->second.first);
        stops.push_back(it->second.second);
    }
    return stops;
}

PositionCollection Board::verticalStops(const Position &position) const {
    PositionCollection stops;
    auto range = verticalBarriers.equal_range(position);
    for (auto it = range.first; it != range.second; ++it) {
        stops.push_back(it->second.first);
        stops.push_back(it->second.second);
    }
    return stops;
}

Position Board::width() const {
    return maxWidth;
}

Position Board::height() const {
    return maxHeight;
}