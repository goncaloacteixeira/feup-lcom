#include <lcom/lcf.h>
#include "video_gr.h"
#include "keyboard.h"
#include "Bitmap.h"
#include "timer.h"
#include "menus.h"

// board["y"]["x"]
int board[22][15];
bool status[22][15];

typedef struct {
	Bitmap* number0;
	Bitmap* number1;
	Bitmap* number2;
	Bitmap* number3;
	Bitmap* number4;
	Bitmap* number5;
	Bitmap* number6;
	Bitmap* number7;
	Bitmap* number8;
	Bitmap* number9;
} numbers;

typedef struct {
	Bitmap* b1;
	Bitmap* b2;
	Bitmap* b3;
	Bitmap* b4;
	Bitmap* b5;
	Bitmap* b6;
	Bitmap* b7;

	int speed;

	int points;

	int current_piece;
	int next_piece;
	int on_hold;

	numbers numbers;

	Bitmap* background;
} tetris;




int* getStatusBoard();

tetris startGame(int speed);

int printPoints(tetris* game);

int fillWithZeros();

int printBoard(tetris* game);

int printNext(tetris* game);

int printOnHold(tetris* game);

/**
 * @return 0 for normal drop
 * @return 1 for early game-over
 * @return 2 for game-over
 */ 
int dropPiece(tetris* game, menus_t* menus);

int desintegrateLines(tetris* game);

int test(tetris* game, menus_t* menus);

int updateFrame(tetris* game);

bool checkNearColisionLeft(tetris* game, int blocks, int pos[][2]);
bool checkNearColisionRight(tetris* game, int blocks, int pos[][2]);
bool checkNearColisionBottom(tetris* game, int blocks, int pos[][2]);

int checkColision(tetris* game, int blocks, int pos[][2]);


int pauseMenu(menus_t* menus);
int gameOverMenu(tetris* game, menus_t* menus);
