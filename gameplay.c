#include "board.h"
#include "gameplay.h"
#include "checks.h"

bool play_again(void)
{
    while (true) {
        char choice;

        printf("\nDo you want to play again? [y/n]\n");
        scanf(" %c", &choice);

        clear_stream();

        switch (choice) {
            case 'y':
            case 'Y':
                return true;
            case 'n':
            case 'N':
                return false;
            default:
                printf("\nInvalid choice input. Try again...\n");
                continue;
        }
    }
}

void greeting(void)
{
    printf("\n\nHey folks, let's play Tick Tack Toe \\o/\n\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    printf("\nThe cells are arranged on the board as follows:");
    print_board(board);
}

void player_message(int player_id, char piece)
{
    printf("\n\nPlayer %d, you are ", player_id);
    change_color(piece);
    printf(" %c ", piece);
    reset_color();
    printf(".\n");
}

void tie_message()
{
    printf("\nIt's a drawn! :'(\n");
}

void won_message(int player_id, char piece, int number_of_moves)
{
    printf("\n\nPlayer %d [", player_id);
    change_color(piece);
    printf(" %c ", piece);
    reset_color();
    printf("] won with %d moves! \\o/\n", number_of_moves);
}

void player_move(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    while (true) {
        int cell, row, column;

        printf("\nEnter an empty cell [1 - 9] you want to place the %c on: ", piece);
        scanf("%d", &cell);

        if (cell < 1 || cell > (BOARD_SIZE * BOARD_SIZE)) {
            printf("\n\nInvalid cell input. Try again...\n\n");
            continue;
        }

        row = (cell - 1) / 3;
        column = (cell - 1) % 3;

        if (board[row][column] != ' ') {
            printf("\n\nThe input cell is already filled. Try again...\n\n");
            continue;
        }

        board[row][column] = piece;
        return;
    }
}

int who_plays_first(player players[NUMBER_OF_PLAYERS])
{
    int first_player_index = (int)(random() % 2);

    printf("\nPlayer %d plays first! \\o/\n", players[first_player_index].id);

    return first_player_index;
}

void gameplay(player players[NUMBER_OF_PLAYERS], char board[BOARD_SIZE][BOARD_SIZE])
{
    int player_index = who_plays_first(players);
    char piece = players[player_index].piece;

    while (true) {
        player_message(player_index + 1, piece);
        print_board(board);
        player_move(piece, board);

        int number_of_moves = ++players[player_index].number_of_moves;

        if (exit_situation(piece, number_of_moves, player_index, board)) {
            return;
        }

        player_index = !player_index;
        piece = players[player_index].piece;
    }
}