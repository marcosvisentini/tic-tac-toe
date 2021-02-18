#ifndef BOARD_H
#define BOARD_H

#include "main.h"

void press_enter(void);
void clear_stream(void);
int set_background_color(char cell);
void change_color(char cell);
void reset_color(void);
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_cell(char cell);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void initial_settings(player players[NUMBER_OF_PLAYERS]);

#endif