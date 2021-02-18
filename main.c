#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 3
#define NUMBER_OF_PLAYERS 2

typedef struct {
    int id;
    char piece;
    int number_of_moves;
} player;

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

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

void tie_message()
{
    printf("\nIt's a drawn! :'(\n");
}

void win_message(int player_id, char piece, int number_of_moves)
{
    printf("\n\nPlayer %d [", player_id);
    change_color(piece);
    printf(" %c ", piece);
    reset_color();
    printf("] won with %d moves! \\o/\n", number_of_moves);
}

bool exit_condition(char piece, int number_of_moves, int player_index, char board[BOARD_SIZE][BOARD_SIZE])
{
    if (check_winner(piece, board)) {
        win_message(player_index + 1, piece, number_of_moves);
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

        if (exit_condition(piece, number_of_moves, player_index, board)) {
            return;
        }

        player_index = !player_index;
        piece = players[player_index].piece;
    }
}

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