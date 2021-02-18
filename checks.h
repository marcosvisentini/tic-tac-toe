#ifndef CHECKS_H
#define CHECKS_H

#include "main.h"

bool check_row(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
bool check_column(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
bool check_main_diagonal(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
bool check_secondary_diagonal(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
bool check_winner(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
bool its_a_draw(char board[BOARD_SIZE][BOARD_SIZE]);
bool exit_situation(char piece, int number_of_moves, int player_index, char board[BOARD_SIZE][BOARD_SIZE]);

#endif