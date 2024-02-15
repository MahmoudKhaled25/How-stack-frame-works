/* 
 * File:   ecu_lcd.h
 * Author: Blu-Ray
 *
 * Created on January 28, 2024, 7:28 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/*Section: Includes*/
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_chr_lcd_cfg.h"

/*Section: Macros*/
#define _LCD_CLEAR_DISPLAY 0x01  
#define _LCD_CURSOR_HOME   0x02

#define _LCD_ENTRY_MODE_SET_SHIFT_ON  0X05
#define _LCD_ENTRY_MODE_SET_DECREMENT 0x04
#define _LCD_ENTRY_MODE_SET_INCREMENT 0x06

#define _LCD_DISPLAY_OFF                 0x08
#define _LCD_DISPLAY_ON                  0x0C
#define _LCD_DISPLAY_UNDERLINE_CURSOR_ON 0x0A
#define _LCD_DISPLAY_BLOCK_CURSOR_ON     0x09

#define _LCD_MOVE_CURSOR_LEFT    0x10
#define _LCD_MOVE_CURSOR_RIGHT   0x14
#define _LCD_SHIFT_DISPLAY_LEFT  0x18
#define _LCD_SHIFT_DISPLAY_RIGHT 0x1C

#define _LCD_FUNCTION_SET_8BIT_INTERFACE 0x30
#define _LCD_FUNCTION_SET_4BIT_INTERFACE 0x20
#define _LCD_FUNCTION_SET_2ROW_MODE      0x28
#define _LCD_FUNCTION_SET_11LINE_MODE    0x24

#define _LCD_CGRAM_START 0x40
#define _LCD_DDRAM_START 0x80

#define DATA_BUS_WIDTH _LCD_INTERFACE_TYPE
/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
typedef struct lcd_pin
{
    uint8 pin_index  : 3;
    uint8 port_index : 3;
    uint8 reserved   : 2;
}chr_lcd_pin_t;

typedef struct lcd
{
    chr_lcd_pin_t rs;
    chr_lcd_pin_t en;
    chr_lcd_pin_t data[DATA_BUS_WIDTH];
}chr_lcd_t;

/*Section: Functions Declarations*/
Std_ReturnType lcd_init(const chr_lcd_t *lcd);
Std_ReturnType lcd_send_command(const chr_lcd_t *lcd, uint8 command);
Std_ReturnType lcd_send_data(const chr_lcd_t *lcd, uint8 data);
Std_ReturnType lcd_send_data_pos(const chr_lcd_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_send_string(const chr_lcd_t *lcd, uint8 *str);
Std_ReturnType lcd_send_string_pos(const chr_lcd_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_send_custom_char(const chr_lcd_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos);

Std_ReturnType convert_uint8_to_string(uint8 val, uint8 str[]);
Std_ReturnType convert_uint16_to_string(uint16 val, uint8 str[]);
Std_ReturnType convert_uint32_to_string(uint32 val, uint8 str[]);
#endif	/* ECU_LCD_H */

