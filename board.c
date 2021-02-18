#include "board.h"

void press_enter(void)
{
    printf("\n[PRESS ENTER TO CONTINUE]\n");

    while (true) {
        int c;
        c = getchar();
        if (c == '\n') {
            break;
        }
    }
}

void clear_stream(void)
{
    int c;

    while (((c = getchar()) != '\n') && (c != EOF)) {
        continue;
    }
}

int set_background_color(char cell)
{
    switch (cell) {
        case 'X':
            return 41;
        case 'O':
            return 44;
        default:
            return 47;
    }
}

void change_color(char cell)
{
    int background_color = set_background_color(cell);

    printf("%c[%d;%dm", 27, 30, background_color);
}

void reset_color(void)
{
    printf("%c[0m", 27);
}

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_cell(char cell)
{
    change_color(cell);
    printf(" %c ", cell);
    reset_color();
    printf("|");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n\n\t+---+---+---+\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\t|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            print_cell(board[i][j]);
        }
        printf("\n\t+---+---+---+\n");
    }
    printf("\n");
}

void initial_settings(player players[NUMBER_OF_PLAYERS])
{
    players[0].id = 1;
    players[0].piece = 'X';
    players[0].number_of_moves = 0;

    players[1].id = 2;
    players[1].piece = 'O';
    players[1].number_of_moves = 0;

    printf("Player 1, you are %c[%d;%dm %c %c[0m.\n", 27, 30, 41, players[0].piece, 27);
    printf("Player 2, you are %c[%d;%dm %c %c[0m.\n\n", 27, 30, 44, players[1].piece, 27);

    press_enter();
}