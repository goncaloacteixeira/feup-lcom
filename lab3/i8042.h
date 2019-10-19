//
// Created by skidr on 14/10/2019.
//

#ifndef LAB3_I8042_H
#define LAB3_I8042_H

#define DELAY_US        20000

#define KBD_IRQ         0x01
#define ESC_MAKE        0x01
#define ESC_BREAK       0x81
#define BUFF_OUT        0x60
#define ST_REG          0x64
#define MSB             0x80

#define TWO_BYTE_CODE   0xE0
#define BREAK_CODE      BIT(7)

// Status register macros
#define OB_FULL         BIT(0) // Outbuffer full
#define IBF_FULL        BIT(1) // InBuffer full, if this is on you can't write commands into the buffer
#define TIMOUT_ERROR    BIT(6) // Data in outbuffer with timeout error
#define PRT_ERROR       BIT(7) // Data in outbuffer with a parity error


#endif //LAB3_I8042_H
