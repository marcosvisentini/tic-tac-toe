#include "board.h"
#include "checks.h"
#include "gameplay.h"

bool check_row(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        int n_pieces_in_a_row = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == piece) {
                n_pieces_in_a_row++;
            }
        }

        if (n_pieces_in_a_row == BOARD_SIZE) {
            return true;
        }
    }

    return false;
}

bool check_column(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        int n_pieces_in_a_column = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i] == piece) {
                n_pieces_in_a_column++;
            }
        }

        if (n_pieces_in_a_column == BOARD_SIZE) {
            return true;
        }
    }

    return false;
}

bool check_main_diagonal(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    int n_pieces_in_main_diagonal = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i] == piece) {
            n_pieces_in_main_diagonal++;
        }
    }

    return (n_pieces_in_main_diagonal == BOARD_SIZE);
}

bool check_secondary_diagonal(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    int n_pieces_in_secondary_diagonal = 0;
    int j = BOARD_SIZE - 1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][j] == piece) {
            n_pieces_in_secondary_diagonal++;
        }
        j--;
    }

    return (n_pieces_in_secondary_diagonal == BOARD_SIZE);
}

bool check_winner(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    return ((check_row(piece, board)) ||
            (check_column(piece, board)) ||
            (check_main_diagonal(piece, board)) ||
            (check_secondary_diagonal(piece, board)));
}

bool its_a_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

bool exit_situation(char piece, int number_of_moves, int player_index, char board[BOARD_SIZE][BOARD_SIZE])
{
    if (check_winner(piece, board)) {
        won_message(player_index + 1, piece, number_of_moves);
        print_board(board);
        return true;
    }

    if (its_a_draw(board)) {
        tie_message();
        print_board(board);
        return true;
    }

    return false;
}