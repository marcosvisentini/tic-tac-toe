#ifndef MAIN_H
#define MAIN_H

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

#endif