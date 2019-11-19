// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "keyboard.h"

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "video_gr.h"
#include "sprite.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  // lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  // lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern uint32_t scancode;
uint32_t irq_set;
extern uint32_t time_counter;


int(video_test_init)(uint16_t mode, uint8_t delay) {

    if (vg_init(mode) == NULL) {
        printf("Error::vg_init(mode)\n");
        return -1;
    }

    sleep(delay);

    if (vg_exit() != 0) {
        printf("Error::vg_exit\n");
        return 1;
    }

    return 0;
}


int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

    int ipc_status;
    message msg;
    uint16_t r;
    uint32_t bit_no;

    bool is_two_byte = false;
    uint8_t scancode_bytes[2];

    if (keyboard_subscribe_int(&bit_no) != 0) {
        return 1;
    }
    irq_set = bit_no;


    if (vg_init(mode) == NULL) {
        printf("Error in vg_init");
        return 1;
    }

    vg_draw_rectangle(x, y, width, height, color);

    while (scancode != ESC_BREAK) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                        kbc_ih();

                        // only reads one byte at a time
                        if (scancode == TWO_BYTE_CODE) {
                            is_two_byte = true;
                            scancode_bytes[0] = scancode;
                        } else {
                            if (is_two_byte) {
                                is_two_byte = false;         // return the variable to its original value
                                scancode_bytes[1] = scancode;
                            } else {
                                scancode_bytes[0] = scancode;
                            }
                        }
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }

    if (keyboard_unsubscribe_int() != 0) {
        return 1;
    }

    if (vg_exit() != OK) {
        printf("Error::vg_init(mode)\n");
        return 1;
    }

    return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

    int ipc_status;
    message msg;
    uint16_t r;
    uint32_t bit_no;

    bool is_two_byte = false;
    uint8_t scancode_bytes[2];

    if (keyboard_subscribe_int(&bit_no) != 0) {
        return 1;
    }
    irq_set = bit_no;

    if (vg_init(mode) == NULL) {
        printf("Error in vg_init");
        return 1;
    }

    if (vg_draw_pattern(no_rectangles, first, step) != 0) {
        return 1;
    }

    while (scancode != ESC_BREAK) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:

                    if (msg.m_notify.interrupts & irq_set) {
                        kbc_ih();

                        if (scancode == TWO_BYTE_CODE) {
                            is_two_byte = true;
                            scancode_bytes[0] = scancode;
                        } else if (is_two_byte) {
                            is_two_byte = false;
                            scancode_bytes[1] = scancode;
                            //scan code complete
                        } else {
                            scancode_bytes[0] = scancode;
                            //scan code complete
                        }
                    }

                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != OK) {
        return 1;
    }

    if (vg_exit() != OK) {
        printf("Error::vg_exit(mode)\n");
        return 1;
    }

    return 0;

}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
    int ipc_status;
    message msg;
    uint16_t r;
    uint32_t bit_no;

    bool is_two_byte = false;
    uint8_t scancode_bytes[2];

    if (keyboard_subscribe_int(&bit_no) != 0) {
        return 1;
    }
    irq_set = bit_no;

    if (vg_init(0x105) == NULL) {
        printf("Error in vg_init");
        return 1;
    }

    vg_draw_pixmap(xpm, x, y);

    while (scancode != ESC_BREAK) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:

                    if (msg.m_notify.interrupts & irq_set) {
                        kbc_ih();

                        if (scancode == TWO_BYTE_CODE) {
                            is_two_byte = true;
                            scancode_bytes[0] = scancode;
                        } else if (is_two_byte) {
                            is_two_byte = false;
                            scancode_bytes[1] = scancode;
                            //scan code complete
                        } else {
                            scancode_bytes[0] = scancode;
                            //scan code complete
                        }
                    }

                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != OK) {
        return 1;
    }

    if (vg_exit() != OK) {
        printf("Error::vg_exit(mode)\n");
        return 1;
    }

    return 0;

}


int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {

    // starts here
    uint8_t irq_set_timer;
    int ipc_status;
    message msg;
    uint16_t r;
    uint32_t bit_no;

    if (timer_subscribe_int(&irq_set_timer) != 0 || keyboard_subscribe_int(&bit_no) != 0) {
        return 1;
    }
    irq_set = bit_no;
    time_counter = 0;

    int fps = 60 / fr_rate;
    int speed_x, speed_y;

    bool flag = false;
    int nCount = 0;
    int nInt;
    if (speed < 0) {
        flag = true;
        nInt = 0 - speed;
        speed = 1;
        speed_x = speed;
        speed_y = speed;
    }

    if (xi != xf) {
        if (xi < xf) {
            speed_y = 0;
            speed_x = speed;
        } else {
            speed_y = 0;
            speed_x = 0 - speed;
        }
    } else {
        if (yi < yf) {
            speed_x = 0;
            speed_y = speed;
        } else {
            speed_x = 0;
            speed_y = 0 - speed;
        }
    }

    Sprite *sprite = create_sprite(xpm, xi, yi, speed_x, speed_y);

    if (vg_init(0x105) == NULL) {
        printf("Error in vg_init");
        return 1;
    }

    vg_draw_sprite(sprite);
    while (scancode != ESC_BREAK) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */

                    if (msg.m_notify.interrupts & irq_set_timer) { /* subscribed interrupt */
                        timer_int_handler();

                        if (time_counter % fps == 0) {
                            if (flag) {
                                nCount++;
                                if (nCount % nInt == 0) {
                                    if (xi < xf || yi < yf) {
                                        if (sprite->x < xf || sprite->y < yf) {
                                            vg_erase_sprite(sprite);
                                            if (sprite->xspeed != 0) {
                                                sprite->x += sprite->xspeed;
                                            } else {
                                                sprite->y += sprite->yspeed;
                                            }
                                            vg_draw_sprite(sprite);
                                        }
                                    } else {
                                        if (xf < xi || yf < yi) {
                                            if (sprite->y > yf || sprite->x > xf) {
                                                vg_erase_sprite(sprite);
                                                if (sprite->xspeed != 0) {
                                                    sprite->x += sprite->xspeed;
                                                } else {
                                                    sprite->y += sprite->yspeed;
                                                }
                                                vg_draw_sprite(sprite);
                                            }
                                        }
                                    }
                                }
                            }
                            else if (xi < xf || yi < yf) {
                                if (sprite->x < xf || sprite->y < yf) {
                                    vg_erase_sprite(sprite);
                                    if (sprite->xspeed != 0) {
                                        sprite->x += sprite->xspeed;
                                    } else {
                                        sprite->y += sprite->yspeed;
                                    }
                                    vg_draw_sprite(sprite);
                                }
                            } else {
                                if (xf < xi || yf < yi) {
                                    if (sprite->y > yf || sprite->x > xf) {
                                        vg_erase_sprite(sprite);
                                        if (sprite->xspeed != 0) {
                                            sprite->x += sprite->xspeed;
                                        } else {
                                            sprite->y += sprite->yspeed;
                                        }
                                        vg_draw_sprite(sprite);
                                    }
                                }
                            }
                        }
                    }

                    if (msg.m_notify.interrupts & irq_set) {
                        kbc_ih();
                    }

                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }


    if (keyboard_unsubscribe_int() != 0) {
        return 1;
    }
    if (timer_unsubscribe_int() != 0) {
        return 1;
    }

    if (vg_exit() != OK) {
        printf("Error::vg_exit(mode)\n");
        return 1;
    }

    return 0;
}

int(video_test_controller)() {
    struct vg_vbe_contr_info vbeContrInfo;
    if (vg_vbe_controller_info(&vbeContrInfo) != 0) {
        printf("cannot get controller info\n");
        return -1;
    }
    vg_display_vbe_contr_info(&vbeContrInfo);
    return 0;
}
