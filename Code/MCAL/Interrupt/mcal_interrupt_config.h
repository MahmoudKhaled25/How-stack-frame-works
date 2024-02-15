/* 
 * File:   mcal_interrupt_config.h
 * Author: Blu-Ray
 *
 * Created on February 12, 2024, 2:08 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/********************************** Includes **********************************/
#include "../std_libraries.h"
#include"../mcal_std_types.h"
#include "../device_config.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"
/*********************************** Macros ***********************************/
#define INTERRUPT_ENABLE   1
#define INTERRUPT_DISABLE  0
#define INTERRUPT_OCCUR    1
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE  0

/********************** Function Like Macro Declarations **********************/
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE)
/* This Macro enables priority levels on interrupts */
#define INTERRUPT_ProiorityLevelsEnable()      (RCONbits.IPEN = 1)

/* This Macro disables priority levels on interrupts */
#define INTERRUPT_ProiorityLevelsDisable()     (RCONbits.IPEN = 0)

/* This Macro enables all high-priority interrupts */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)

/* This Macro disable all high-priority interrupts */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/* This Macro enables all low-priority interrupts */
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)

/* This Macro disable all low-priority interrupts */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)
#else

/* This Macro enables all unmasked interrupts */
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)

/* This Macro disables all interrupts */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/* This Macro enables all unmasked peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)

/* This Macro disable all peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif
/*************************** Data Types Declarations **************************/
#if (INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE)
typedef enum {
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;
#endif
/*************************** Functions Declarations ***************************/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

