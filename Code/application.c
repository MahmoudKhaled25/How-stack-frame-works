/*
 * File:   application.c
 * Author: Mahmoud Khaled
 *
 * Created on February 11, 2024, 5:01 AM
 */

/********************************** Includes **********************************/
#include "application.h"

/*********************************** Macros ***********************************/

/*********************** Function Like Macro Declarations *********************/

/************************** Data Types Declarations ***************************/

/***************************** Global Declarations ****************************/
uint8 set_1st_clear_4th(uint8 num);
uint8 clear_4th(uint8 num);
Std_ReturnType ret_val;
uint8 read;

int main() 
{ 
    app_init();
    
    while (1)
    {
        ret_val = keypad_read_button(&keypad, &read);
        
        if(read)
        {
            read = set_1st_clear_4th(read);
            ret_val = lcd_send_data(&lcd, read);
            read = 0;
            __delay_ms(250);
        }
    }
}

/******************************* Sub-Functions ********************************/
uint8 set_1st_clear_4th(uint8 num)
{
    num |= 0x01;    // set 1st LSB
    uint8 buff = clear_4th(num);  // Function Call
    return buff;
}

uint8 clear_4th(uint8 num)
{
    num &= ~(0x01 << 3); // Clear 4th LSB
    return num;
}

void app_init()
{
    ret_val = ecu_layer_initialize();
}