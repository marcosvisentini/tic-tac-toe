#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main.h"

bool play_again(void);
void greeting(void);
void player_message(int player_id, char piece);
void tie_message();
void won_message(int player_id, char piece, int number_of_moves);
void player_move(char piece, char board[BOARD_SIZE][BOARD_SIZE]);
int who_plays_first(player players[NUMBER_OF_PLAYERS]);
void gameplay(player players[NUMBER_OF_PLAYERS], char board[BOARD_SIZE][BOARD_SIZE]);

#endif