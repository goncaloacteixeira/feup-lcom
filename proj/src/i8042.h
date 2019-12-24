//
// Created by skidr on 14/10/2019.
//

#ifndef LAB3_I8042_H
#define LAB3_I8042_H

#define DELAY_US        10000

#define KBD_IRQ         0x01
#define ESC_MAKE        0x01
#define ESC_BREAK       0x81

#define LEFT_MAKE       0x4b
#define RIGHT_MAKE      0x4d
#define DOWN_MAKE       0x50
#define A_MAKE          0x1e
#define D_MAKE          0xa0
#define UP_MAKE         0x48
#define SPACE_MAKE      0x39
#define ENTER_MAKE      0x1c

#define BUFF_OUT        0x60
#define ST_REG          0x64
#define MSB             0x80

#define TWO_BYTE_CODE   0xE0
#define BREAK_CODE      BIT(7)

// MOUSE
#define LB              BIT(0)
#define RB              BIT(1)
#define MB              BIT(2)
#define CHECK_BYTE1     BIT(3)
#define X_NEG           BIT(4)
#define Y_NEG           BIT(5)
#define X_OV            BIT(6)
#define Y_OV            BIT(7)

#define IRQ_MOUSE       12
#define IBF_FULL        BIT(1)
#define DIS_MOUSE       0xFD    // 1111 1101
#define EN_MOUSE        0x02    // 0000 0010

#define CMD_INIT        0xD4 	// Write byte do mouse
#define CMD_REG         0x64    // Keyboard command register

#define ACK             0xFA	// If everything OK
#define NACK            0xFE

#define REMOTE          0xF0
#define ENABLE          0xF4
#define DISABLE         0xF5

#define SET_STREAM      0xEA
#define READ            0xEB
#define ENABLE_KB_MOU   0xCC
#define BUF_OUT         0x60
#define BUF_IN	 	      0x60

// Status register macros
#define OB_FULL         BIT(0) // Outbuffer full
#define IB_FULL        BIT(1) // InBuffer full, if this is on you can't write commands into the buffer
#define TIMEOUT_ERROR    BIT(6) // Data in outbuffer with timeout error
#define PRT_ERROR       BIT(7) // Data in outbuffer with a parity error


#endif //LAB3_I8042_H
