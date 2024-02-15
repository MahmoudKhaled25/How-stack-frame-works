#include "ecu_layer_init.h"

chr_lcd_t lcd = {
    .data = {
        [0] = {PIN0, PORTC_INDEX},
        [1] = {PIN1, PORTC_INDEX},
        [2] = {PIN2, PORTC_INDEX},
        [3] = {PIN3, PORTC_INDEX}
    },
    .en = {PIN4, PORTC_INDEX},
    .rs = {PIN5, PORTC_INDEX}
};

keypad_t keypad = {
    .keypad_row_pins = {
        [R0] = {PORTD_INDEX, PIN0},
        [R1] = {PORTD_INDEX, PIN1},
        [R2] = {PORTD_INDEX, PIN2},
        [R3] = {PORTD_INDEX, PIN3}
    },
    .keypad_column_pins = {
        [C0] = {PORTD_INDEX, PIN4},
        [C1] = {PORTD_INDEX, PIN5},
        [C2] = {PORTD_INDEX, PIN6},
        [C3] = {PORTD_INDEX, PIN7},
    },
    .keypad_type = KEYPAD_ACTIVE_HIGH
};

Std_ReturnType ecu_layer_initialize()
{
    Std_ReturnType ret_val = E_OK;
    ret_val = keypad_init(&keypad);
    ret_val = lcd_init(&lcd);
    
    return ret_val;
}
