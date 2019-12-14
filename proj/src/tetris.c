#include "tetris.h"


tetris startTetris() {
	tetris game;

    printf("**// STARTING GAME //**\n");
	printf("**loading pieces...**\n");

	game.piece1 = createPiece(1);
	game.piece2 = createPiece(2);
	game.piece3 = createPiece(3);
	game.piece4 = createPiece(4);
	game.piece5 = createPiece(5);
	game.piece6 = createPiece(6);
	game.piece7 = createPiece(7);
	game.piece8 = createPiece(8);
	game.piece9 = createPiece(9);
	game.piece10 = createPiece(10);
	game.piece11 = createPiece(11);
	game.piece12 = createPiece(12);

	printf("**loading background1**\n");
	game.background = loadBitmap("/home/lcom/labs/proj/res/background.bmp");

	printf("**tetris started successfully!**\n");
	return game;
}

piece_t* getRandomPiece(tetris* game) {
	int code = rand() % (12 + 1 - 1) + 1;

	printf("getting piece %d\n", code);
	switch (code) {
	case 1:
		return &game->piece1;
	case 2:
		return &game->piece2;
	case 3:
		return &game->piece3;
	case 4:
		return &game->piece4;
	case 5:
		return &game->piece5;
	case 6:
		return &game->piece6;
	case 7:
		return &game->piece7;
	case 8:
		return &game->piece8;
	case 9:
		return &game->piece9;
	case 10:
		return &game->piece10;
	case 11:
		return &game->piece11;
	case 12:
		return &game->piece12;										
	default:
		break;
	}
	return 0;
}


piece_t createPiece(int block) {
    const char *path0;
    const char *path1;
    const char *path2;
    const char *path3;

    piece_t piece;
	
    switch (block) {
        case 1:
			path0 = "/home/lcom/labs/proj/res/block1.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path0);
            piece.rotation2 = loadBitmap(path0);
            piece.rotation3 = loadBitmap(path0);
            piece.rotation = 0;
            piece.block = 1;
            
            // dimensões
            piece.dimension.height = 32;
            piece.dimension.width = 32;

			printf("block1 created successfully\n");
            return piece;
		case 2:
            path0 = "/home/lcom/labs/proj/res/block2_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block2_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block2_1.bmp";
            path3 = "/home/lcom/labs/proj/res/block2_2.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 2;

            // dimensões
            piece.dimension.height = 32;
            piece.dimension.width = 64;

			printf("block2 created successfully\n");
            return piece;
        case 3:
            path0 = "/home/lcom/labs/proj/res/block3_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block3_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block3_1.bmp";
            path3 = "/home/lcom/labs/proj/res/block3_2.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 3;

            // dimensões
            piece.dimension.height = 32;
            piece.dimension.width = 96;

			printf("block3 created successfully\n");
            return piece;
        case 4:
            path0 = "/home/lcom/labs/proj/res/block4_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block4_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block4_1.bmp";
            path3 = "/home/lcom/labs/proj/res/block4_2.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 4;

            // dimensões
            piece.dimension.height = 32;
            piece.dimension.width = 128;

			printf("block4 created successfully\n");
            return piece;
        case 5:
            path0 = "/home/lcom/labs/proj/res/block5.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path0);
            piece.rotation2 = loadBitmap(path0);
            piece.rotation3 = loadBitmap(path0);
            piece.rotation = 0;
            piece.block = 5;

            // dimensões
            piece.dimension.height = 64;
            piece.dimension.width = 64;

			printf("block5 created successfully\n");
            return piece;
        case 6:
            path0 = "/home/lcom/labs/proj/res/block6_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block6_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block6_3.bmp";
            path3 = "/home/lcom/labs/proj/res/block6_4.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 6;

            // dimensões
            piece.dimension.height = 64;
            piece.dimension.width = 96;

			printf("block6 created successfully\n");
            return piece;
        case 7:
            path0 = "/home/lcom/labs/proj/res/block7_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block7_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block7_3.bmp";
            path3 = "/home/lcom/labs/proj/res/block7_4.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 7;

            // dimensões
            piece.dimension.height = 64;
            piece.dimension.width = 96;

			printf("block7 created successfully\n");
            return piece;
        case 8:
            path0 = "/home/lcom/labs/proj/res/block8_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block8_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block8_1.bmp";
            path3 = "/home/lcom/labs/proj/res/block8_2.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 8;

            // dimensões
            piece.dimension.height = 96;
            piece.dimension.width = 64;

			printf("block8 created successfully\n");
            return piece;
        case 9:
            path0 = "/home/lcom/labs/proj/res/block9_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block9_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block9_1.bmp";
            path3 = "/home/lcom/labs/proj/res/block9_2.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 9;

            // dimensões
            piece.dimension.height = 96;
            piece.dimension.width = 64;

			printf("block9 created successfully\n");
            return piece;
        case 10:
            path0 = "/home/lcom/labs/proj/res/block10_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block10_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block10_3.bmp";
            path3 = "/home/lcom/labs/proj/res/block10_4.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 10;

            // dimensões
            piece.dimension.height = 64;
            piece.dimension.width = 96;

			printf("block10 created successfully\n");
            return piece;
        case 11:
            path0 = "/home/lcom/labs/proj/res/block11_1.bmp";
            path1 = "/home/lcom/labs/proj/res/block11_2.bmp";
            path2 = "/home/lcom/labs/proj/res/block11_3.bmp";
            path3 = "/home/lcom/labs/proj/res/block11_4.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path1);
            piece.rotation2 = loadBitmap(path2);
            piece.rotation3 = loadBitmap(path3);
            piece.rotation = 0;
            piece.block = 11;

            // dimensões
            piece.dimension.height = 64;
            piece.dimension.width = 64;

			printf("block11 created successfully\n");
            return piece;
        case 12:
            path0 = "/home/lcom/labs/proj/res/block12.bmp";
            piece.rotation0 = loadBitmap(path0);
            piece.rotation1 = loadBitmap(path0);
            piece.rotation2 = loadBitmap(path0);
            piece.rotation3 = loadBitmap(path0);
            piece.rotation = 0;
            piece.block = 12;

            // dimensões
            piece.dimension.height = 96;
            piece.dimension.width = 96;

			printf("block12 created successfully\n");
            return piece;
        default:
            break;
    }

    return piece;
}


int drawPiece(piece_t* piece, int x, int y, int rotation) {
    if (rotation == 0) {
        drawBitmap(piece->rotation0, x, y, getAuxBuffer());
        return 0;
    }
    if (rotation == 1) {
        drawBitmap(piece->rotation1, x, y, getAuxBuffer());
        return 0;
    }
    if (rotation == 2) {
        drawBitmap(piece->rotation2, x, y, getAuxBuffer());
        return 0;
    }
    if (rotation == 3) {
        drawBitmap(piece->rotation3, x, y, getAuxBuffer());
        return 0;
    }
    printf("no valid rotation number\n");
    return 1;
}


extern uint32_t scancode;
extern uint32_t irq_set;
extern uint32_t time_counter;
extern uint8_t irq_set_timer;

int dropPiece(piece_t* piece, int speed) {
    
    int ipc_status;
    message msg;
    uint16_t r;
    // uint32_t bit_no;

    int rotation = 0;
    int x = 462;
    int y = 32;

    time_counter = 0;
    int fps = 30 * 32 / (speed);

    bool is_two_byte = false;   
    uint8_t scancode_bytes[2];


	printf("dropping piece %d\n", piece->block);

    bool wait = false;
    bool bound = true;

    while (scancode != ESC_MAKE && bound) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */

                    if (msg.m_notify.interrupts & irq_set_timer) {
                        timer_int_handler();

                        if (time_counter % fps == 0) {
                            if (wait)
                                tickdelay(micros_to_ticks(DELAY_US));
                            updateFrame();
                            drawPiece(piece, x, y, rotation);
                            //
                            doubleBuffering();
                            y += 32;
                            if (piece->rotation == 0 || piece->rotation == 2) {
                                if (768 <= piece->dimension.height + y) {
                                    bound = false;
                                    break;
                                }
                            }
                            else if (piece->rotation == 1 || piece->rotation == 3) {
                                if (768 <= piece->dimension.width + y) {
                                    bound = false;
                                    break;
                                }
                            }
                            //
                        }
                    }

                    if (msg.m_notify.interrupts & irq_set) {
                        kbc_ih();
                        // only reads one byte at a time
                        if (scancode == TWO_BYTE_CODE) {
                            is_two_byte = true;
                            scancode_bytes[0] = scancode;
                        } else {
                            if (is_two_byte) {
                                is_two_byte = false;
                                scancode_bytes[1] = scancode;
                            } else {
                                scancode_bytes[0] = scancode;
                            }
                        }

                        // SIDE MOVEMENTS
                        if (scancode_bytes[1] == LEFT_MAKE) {
                            if (x-32 >= 270) {
                                wait = true;
                                updateFrame();
                                x -= 32;
                                //
                                if (x < 270) {
                                    x += 32;
                                }
                                //
                                drawPiece(piece, x, y, rotation);
                                doubleBuffering();
                                
                                scancode_bytes[1] = 0;
                            }
                        }
                        if (scancode_bytes[1] == RIGHT_MAKE) {
                            wait = true;
                            x += 32;
                            updateFrame();
                            if (piece->rotation == 0 || piece->rotation == 2) {
                                if (piece->dimension.width + x > 750) {
                                    x -= 32;
                                }
                            }
                            else if (piece->rotation == 1 || piece->rotation == 3) {
                                if (piece->dimension.height + x > 750) {
                                    x -= 32;
                                }
                            }
                            drawPiece(piece, x, y, rotation);
                            doubleBuffering();
                            
                            scancode_bytes[1] = 0;
                        }

                        // Rotation
                        if (scancode == A_MAKE) {
                            wait = true;
                            updateFrame();
                            rotation -= 1;
                            if (rotation == -1)
                                rotation = 3;
                            piece->rotation = rotation;
                            drawPiece(piece, x, y, rotation);
                            doubleBuffering();
                        }
                        if (scancode == D_MAKE) {
                            wait = true;
                            updateFrame();
                            rotation += 1;
                            if (rotation == 4)
                                rotation = 0;
                            piece->rotation = rotation;
                            if (piece->rotation == 0 || piece->rotation == 2) {
                                if (piece->dimension.width + x > 750) {
                                    x -= piece->dimension.width + x - 750;
                                }
                            }
                            else if (piece->rotation == 1 || piece->rotation == 3) {
                                if (piece->dimension.height + x > 750) {
                                    x -= piece->dimension.height + x- 750;
                                }
                            }
                            drawPiece(piece,x,y,rotation);
                            doubleBuffering();
                        }

                        // SPEED UP DOWN MOVEMENT
                        if (scancode_bytes[1] == DOWN_MAKE) {
                            updateFrame();
                            drawPiece(piece, x, y, rotation);
                            doubleBuffering();
                            y += 32;
                            if (piece->rotation == 0 || piece->rotation == 2) {
                                if (768 <= piece->dimension.height + y) {
                                    bound = false;
                                    break;
                                }
                            }
                            else if (piece->rotation == 1 || piece->rotation == 3) {
                                if (768 <= piece->dimension.width + y) {
                                    bound = false;
                                    break;
                                }
                            }
                            scancode_bytes[1] = 0;
                        }
                    
                        wait = false;
                    }

                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }
    scancode = 0;
    return 0;
}



int drawGameBackground(tetris* game) {
	drawBitmap(game->background, 0, 0, getAuxBuffer());
	return 0;
}


char* gameStatus;

uint32_t irq_set;
uint8_t irq_set_timer;

int startNewGame(tetris* game, int speed) {

	uint32_t bit_no;
	if (timer_subscribe_int(&irq_set_timer) != 0 || keyboard_subscribe_int(&bit_no) != 0) {
        return 1;
    }
    irq_set = bit_no;


	gameStatus = (char *) malloc(getVRAMSize());

	if (saveGameStatus() != 0) {
    	printf("cannot save game status\n");
        return 1;
    }

	int i = 7;
	do {
		piece_t* piece = getRandomPiece(game);
		dropPiece(piece, speed);
		i--;
		if (saveGameStatus() != 0) {
        	printf("cannot save game status\n");
        	return 1;
    	}
	} while (i != 0);

    if (keyboard_unsubscribe_int() != 0) {
        return 1;
    }
    if (timer_unsubscribe_int() != 0) {
        return 1;
    }
	
	return 0;
}

int saveGameStatus() {
    memcpy(gameStatus, getAuxBuffer(), getVRAMSize());
    return 0;
}

char* getGameStatus() {
    return gameStatus;
}
