#include "main.h"
#include "board.h"
#include "checks.h"
#include "gameplay.h"

int main(void)
{
    srand(time(NULL));

    do {
        char board[BOARD_SIZE][BOARD_SIZE];
        player players[NUMBER_OF_PLAYERS];

        greeting();
        initial_settings(players);
        initialize_board(board);
        gameplay(players, board);
    } while (play_again());

    return 0;
}