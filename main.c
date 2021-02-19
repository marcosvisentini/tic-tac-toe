#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        char c = getchar();
        if (c == '\n') {
            break;
        }
    }
}

void clear_stream(void)
{
    char c;

    while (((c = getchar()) != '\n') && (c != EOF)) {
        continue;
    }
}

void sleep_ms(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
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
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n\n\t+---+---+---+\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\t|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            print_cell(board[i][j]);
            printf("|");
        }
        printf("\n\t+---+---+---+\n");
    }
    printf("\n");
}

void print_players_info(int chosen_game_mode, 
                        player players[NUMBER_OF_PLAYERS])
{
    if (chosen_game_mode == 1) {
        printf("Player 1, you are ");
        print_cell(players[0].piece);
        printf("\n");
        printf("Player 2, you are ");
        print_cell(players[1].piece);
        printf("\n\n");
    } else {
        printf("Human, you are   ");
        print_cell(players[0].piece);
        printf("\n");
        printf("Computer is      ");
        print_cell(players[1].piece);
        printf("\n\n");
    }
}

void initial_settings(int chosen_game_mode,
                      player players[NUMBER_OF_PLAYERS])
{
    players[0].id = 1;
    players[0].piece = 'X';
    players[0].number_of_moves = 0;

    players[1].id = 2;
    players[1].piece = 'O';
    players[1].number_of_moves = 0;

    print_players_info(chosen_game_mode, players);
    clear_stream();
    press_enter();
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

void win_message(int chosen_game_mode, int player_id,
                 char piece, int number_of_moves)
{
    if (chosen_game_mode == 1) {
        printf("\n\nPlayer %d [", player_id);
    } else {
        if (player_id == 1) {
            printf("\n\nHuman [");
        } else {
            printf("\n\nComputer [");
        }
    }

    print_cell(piece);
    printf("] won with %d moves! \\o/\n", number_of_moves);
}

bool exit_condition(int chosen_game_mode, char piece, int number_of_moves,
                    int player_index, char board[BOARD_SIZE][BOARD_SIZE])
{
    if (check_winner(piece, board)) {
        win_message(chosen_game_mode, player_index + 1, piece, number_of_moves);
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
                printf("\nInvalid input. Try again...\n");
                continue;
        }
    }
}

void greeting(void)
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    printf("\nThe cells are arranged on the board as follows:");
    print_board(board);
}

void player_message(int chosen_game_mode, int player_id, char piece)
{
    if (chosen_game_mode == 1) {
        printf("\nPlayer %d, you are ", player_id);
    } else {
        if (player_id == 1) {
            printf("\nHuman, you are ");
        } else {
            printf("\nComputer is ");
        }
    }

    print_cell(piece);
    printf(".\n");
}

void player_move(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    while (true) {
        int cell, row, column;

        printf("\nEnter an empty cell [1 - 9] you want to place the ");
        print_cell(piece);
        printf(" on: ");

        scanf("%d", &cell);

        if (cell < 1 || cell > (BOARD_SIZE * BOARD_SIZE)) {
            printf("\n\nInvalid input. Try again...\n\n");
            continue;
        }

        row = (cell - 1) / 3;
        column = (cell - 1) % 3;

        if (board[row][column] != ' ') {
            printf("\n\nThe entered cell is already filled. Try again...\n\n");
            continue;
        }

        board[row][column] = piece;
        return;
    }
}

void computer_move(char piece, char board[BOARD_SIZE][BOARD_SIZE])
{
    while (true) {
        int row = rand() % BOARD_SIZE;
        int column = rand() % BOARD_SIZE;

        if (board[row][column] != ' ') {
            continue;
        }

        board[row][column] = piece;
        break;
    }
}

int who_plays_first(int chosen_game_mode)
{
    int first_player_index = (int)(random() % 2);

    sleep_ms((random() % (2000 - 1000 + 1)) + 1000);

    if (chosen_game_mode == 1) {
        printf("\nPlayer %d plays first! \\o/\n", first_player_index + 1);
    } else {
        if (first_player_index == 0) {
            printf("\nHuman plays first! \\o/\n");
        } else {
            printf("\nComputer plays first! \\o/\n");
        }
    }

    return first_player_index;
}

void gameplay(int chosen_game_mode, player players[NUMBER_OF_PLAYERS],
              char board[BOARD_SIZE][BOARD_SIZE])
{
    int player_index = who_plays_first(chosen_game_mode);
    char piece = players[player_index].piece;

    print_board(board);

    while (true) {
        player_message(chosen_game_mode, player_index + 1, piece);

        if (chosen_game_mode == 1) {
            player_move(piece, board);
        } else {
            if (player_index == 0) {
                player_move(piece, board);
            } else {
                computer_move(piece, board);
                sleep_ms((random() % (2000 - 1000 + 1)) + 1000);
            }
        }
        
        print_board(board);

        int number_of_moves = ++players[player_index].number_of_moves;

        if (exit_condition(chosen_game_mode, piece, number_of_moves,
                           player_index, board)) {
            return;
        }

        player_index = !player_index;
        piece = players[player_index].piece;
    }
}

int game_mode(void)
{
    printf("\n\nHey folks, let's play Tick Tack Toe \\o/\n\n");

    while (true) {
        int chosen_game_mode;

        printf("\nChoose a game mode:\n");
        printf("\n1. PLAYER 1  vs  PLAYER 2");
        printf("\n2. HUMAN     vs  COMPUTER\n\n");
        scanf("%d", &chosen_game_mode);
 
        if (chosen_game_mode < 1 || chosen_game_mode > 2) {
            printf("\nInvalid input. Try again...\n");
            continue;
        }
 
        greeting();
        return chosen_game_mode;
    }
}

int main(void)
{
    srand(time(NULL));

    do {
        char board[BOARD_SIZE][BOARD_SIZE];
        player players[NUMBER_OF_PLAYERS];

        int chosen_game_mode = game_mode();
        initial_settings(chosen_game_mode, players);
        initialize_board(board);
        gameplay(chosen_game_mode, players, board);
    } while (play_again());

    return 0;
}