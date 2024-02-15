/* 
 * File:   ecu_layer_init.h
 * Author: Blu-Ray
 *
 * Created on November 1, 2023, 4:04 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


/*Section: Includes*/
#include "Keypad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"

/*Section: Macros*/

/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
extern chr_lcd_t lcd;
extern keypad_t keypad;
/*Section: Functions Declarations*/
Std_ReturnType ecu_layer_initialize();

#endif	/* ECU_LAYER_INIT_H */

