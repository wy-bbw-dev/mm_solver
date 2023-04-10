//
// Created by ich on 3/27/23.
//

#include <model/Board.h>
#include <model/Meeple.h>
#include <view/ascii/BoardPrinter.h>
#include <string>
#include <stdexcept>

#include <spdlog/spdlog.h>


namespace {

    const auto PRINT_WIDTH = [] (const Board& board) { return 2 * board.width() + 3;};
    const auto PRINT_HEIGHT = [] (const Board& board) { return 2 * board.height() + 2;};

    void add_linebreaks(const Board& board, ascii::BoardString& board_string) {
        for (auto i = 0; i < PRINT_HEIGHT(board); ++i) {
            const auto linebreak_position = i * PRINT_WIDTH(board) + PRINT_WIDTH(board) - 1;
            board_string[linebreak_position] = '\n';
        }
    }

    void printAxis(const Board& board, ascii::BoardString& board_string) {
        for (Position i = 0; i < board.width(); ++i) {
            board_string[2 * i + 2] = 'A' + i;
        }
        for (Position i = 0; i < board.height(); ++i) {
            board_string[(2 * i + 2) * PRINT_WIDTH(board)] = 'A' + i;
        }
    }
    void printFrame(const Board& board,  ascii::BoardString& board_string) {
        for (int i = 2; i < PRINT_WIDTH(board) - 1; ++i) {
            board_string[PRINT_WIDTH(board) + i] = '-';
            board_string[i + (PRINT_HEIGHT(board) - 1) * PRINT_WIDTH(board)] = '-';
        }

        for (int i = 1; i < PRINT_HEIGHT(board); ++i) {
            board_string[i * PRINT_WIDTH(board) + 1] = '|';
            board_string[i * PRINT_WIDTH(board) + PRINT_WIDTH(board) - 2] = '|';
        }
    }

    Position string_index(const Board& board, const Coordinate coordinate) {
        return (2 * coordinate.second + 2)  * PRINT_WIDTH(board) + 2 * coordinate.first + 2;

    }

    void printMeeples(const Board &board, ascii::BoardString &board_string) {

        for (int i = 0; i < 8; ++i) {
            const Meeple meeple = static_cast<Meeple>(i);
            try {
                const auto meeple_coordinate = board.meeple_location(meeple);
                board_string[string_index(board, meeple_coordinate)] = '0' + static_cast<unsigned char>(i);
            } catch (const std::out_of_range &e) {
//                spdlog::info("Meeple " + std::to_string(static_cast<int>(meeple)) + " not found");
 // TODO: proper logging
            }
        }
    }

    void printTeleports(const Board &board, ascii::BoardString &board_string) {
        for (const auto& teleport : board.teleport_locations()) {
            board_string[string_index(board, teleport)] = 'T';
        }
    }

    void printBarriers(const Board &board, ascii::BoardString &board_string) {
        for (int i = 0; i < board.height(); ++i) {
            PositionCollection barriers = board.horizontal_barriers(i);
            for (const Position barrier_position : barriers) {
                Position index = string_index(board, {i, barrier_position });
                board_string[index + 1] = '|';
            }
        }

        for (int i = 0; i < board.width(); ++i) {
            PositionCollection barriers = board.vertical_barriers(i);
            for (const Position barrier_position : barriers) {
                Position index = string_index(board, {barrier_position, i});
                board_string[index + PRINT_WIDTH(board)] = '-';
            }
        }
    }
}

ascii::BoardString ascii::print(const Board& board) {
    ascii::BoardString board_string;
    board_string.resize(PRINT_WIDTH(board) * PRINT_HEIGHT(board));

    // initialize board_string with spaces
    std::ranges::fill(board_string, ' ');

    add_linebreaks(board, board_string);
    printAxis(board, board_string);
    printFrame(board, board_string);
    printTeleports(board, board_string);
    printBarriers(board, board_string);
    printMeeples(board, board_string);
    return board_string;
}