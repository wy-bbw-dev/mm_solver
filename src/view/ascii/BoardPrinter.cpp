//
// Created by ich on 3/27/23.
//

#include <model/Board.h>
#include <view/ascii/BoardPrinter.h>
#include <string>


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
        for (auto i = 0; i < board.width(); ++i) {
            board_string[2 * i + 2] = 'A' + i;
        }
        for (auto i = 0; i < board.height(); ++i) {
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
}

ascii::BoardString ascii::print(const Board& board) {
    ascii::BoardString board_string;
    board_string.resize(PRINT_WIDTH(board) * PRINT_HEIGHT(board));

    // initialize board_string with spaces
    std::fill(board_string.begin(), board_string.end(), ' ');

    add_linebreaks(board, board_string);
    printAxis(board, board_string);
    printFrame(board, board_string);
    return board_string;
}