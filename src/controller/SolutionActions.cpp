//
// Created by ich on 4/15/23.
//

#include <controller/SolutionActions.h>

void solution::apply(const Solution& solution, Board& board) {
    for (const auto& [meeple, moves] : solution.moves_by_meeple) {
        for (const auto& move : moves) {
            board.place_meeple(meeple, move.to);
        }
    }
}