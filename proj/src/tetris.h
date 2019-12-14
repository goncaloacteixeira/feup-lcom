#include "lcom/lcf.h"
#include "Bitmap.h"
#include "keyboard.h"
#include "video_gr.h"

typedef struct {
	int height;
	int width;
} dimension_t;


typedef struct {
  Bitmap* rotation0;
  Bitmap* rotation1;
  Bitmap* rotation2;
  Bitmap* rotation3;
  int rotation;
  int block;
	dimension_t dimension;
} piece_t;

typedef struct {
	piece_t piece1;
	piece_t piece2;
	piece_t piece3;
	piece_t piece4;
	piece_t piece5;
	piece_t piece6;
	piece_t piece7;
	piece_t piece8;
  piece_t piece9;
	piece_t piece10;
	piece_t piece11;
	piece_t piece12;

	Bitmap* background;	
} tetris;



piece_t createPiece(int block);
int drawPiece(piece_t* piece, int x, int y, int rotation);
int dropPiece(piece_t* piece, int speed);


tetris startTetris();

int drawGameBackground(tetris* game);

int saveGameStatus();
char* getGameStatus();

int startNewGame(tetris* game, int speed);
