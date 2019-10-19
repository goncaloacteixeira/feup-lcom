#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "timer.h"

extern uint32_t scancode;
extern uint32_t sys_inb_counter;

extern uint32_t time_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

uint32_t irq_set;

int(kbd_test_scan)() {
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

    while(scancode != ESC_BREAK) {
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
                                // function provided
                                kbd_print_scancode(!(BREAK_CODE & scancode), 2, scancode_bytes);
                            } else {
                                scancode_bytes[0] = scancode;
                                kbd_print_scancode(!(BREAK_CODE & scancode), 1, scancode_bytes);
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

    kbd_print_no_sysinb(sys_inb_counter);
    return 0;
}

int(kbd_test_poll)() {
    scancode = 0;
    bool is_two_byte = false;
    uint8_t scancode_bytes[2];
    sys_inb_counter = 0;

    while (scancode != ESC_BREAK) {
        if (kbc_poll() == 0) {
            if (scancode == TWO_BYTE_CODE) {
                is_two_byte = true;
                scancode_bytes[0] = scancode;
            } else {
                if (is_two_byte == true) {
                    is_two_byte = false;         // return the variable to its original value
                    scancode_bytes[1] = scancode;
                    // function provided
                    kbd_print_scancode(!(BREAK_CODE & scancode), 2, scancode_bytes);
                } else {
                    scancode_bytes[0] = scancode;
                    kbd_print_scancode(!(BREAK_CODE & scancode), 1, scancode_bytes);
                }
            }
        }
        else {
            continue;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }

    {
        uint8_t command;

        if (sys_outb(ST_REG, 0x20) != 0) {
            printf("Error::sys_outb(ST_REG, 0x20)\n");
            return 1;
        }

        if (sys_inb_kbd(BUFF_OUT, &command) != 0) {
            printf("Error::sys_inb_kbd(BUFF_OUT, &command)\n");
            return 1;
        }

        command |= 0x01;

        if (sys_outb(ST_REG, BUFF_OUT) != 0) {
            printf("Error::sys_outb(ST_REG, BUFF_OUT)\n");
            return 1;
        }

        if (sys_outb(BUFF_OUT, command) != 0) {
            printf("Error::sys_outb(BUFF_OUT, command)\n");
            return 1;
        }
    }

    kbd_print_no_sysinb(sys_inb_counter);
    sys_inb_counter = 0;
    return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {

    int ipc_status;
    message msg;
    uint16_t r;
    // uint32_t bit_no;

    uint8_t irq_set_timer;

    bool is_two_byte = false;
    uint8_t scancode_bytes[2];

    if (keyboard_subscribe_int(&irq_set) != 0 || timer_subscribe_int(&irq_set_timer) != 0) {
        return 1;
    }

    while(scancode != ESC_BREAK && time_counter < (n * 60)) {
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
                    }
                    if (msg.m_notify.interrupts & irq_set) {
                        kbc_ih();
                        // only reads one byte at a time
                        if (scancode == TWO_BYTE_CODE) {
                            is_two_byte = true;
                            scancode_bytes[0] = scancode;
                        } else {
                            if (is_two_byte) {
                                is_two_byte = false;         // return the variable to its original value
                                scancode_bytes[1] = scancode;
                                // function provided
                                kbd_print_scancode(!(BREAK_CODE & scancode), 2, scancode_bytes);
                            } else {
                                scancode_bytes[0] = scancode;
                                kbd_print_scancode(!(BREAK_CODE & scancode), 1, scancode_bytes);
                            }
                        }
                        time_counter = 0;
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

    kbd_print_no_sysinb(sys_inb_counter);
    return 0;
}
